#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Unit.h"
#include "GameRoom.h"
#include "Game.h"
//#include "DatabaseJobContext.h"
//#include "DatabaseJobManager.h"

//@{ Handler Helper

typedef void(*HandlerFunc)(ClientSession* session);

static HandlerFunc HandlerTable[PKT_MAX];

static void DefaultHandler(ClientSession* session)
{
	printf("[DEBUG] Invalid packet handler \n");
	session->Disconnect();
}

struct InitializeHandlers
{
	InitializeHandlers()
	{
		for (int i = 0; i < PKT_MAX; ++i)
			HandlerTable[i] = DefaultHandler;
	}
} _init_handlers_;

struct RegisterHandler
{
	RegisterHandler(int pktType, HandlerFunc handler)
	{
		HandlerTable[pktType] = handler;
	}
};

#define REGISTER_HANDLER(PKT_TYPE)	\
	static void Handler_##PKT_TYPE(ClientSession* session); \
	static RegisterHandler _register_##PKT_TYPE(PKT_TYPE, Handler_##PKT_TYPE); \
	static void Handler_##PKT_TYPE(ClientSession* session)

//@}



///////////////////////////////////////////////////////////////////////////
/*
	연결된 클라이언트와 패킷 받고 보내는 작업 완료하는 콜백 함수들
	*/
///////////////////////////////////////////////////////////////////////////
void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// 에러 발생시 해당 세션 종료
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	/// 받은 데이터 처리
	fromClient->OnRead(cbTransferred);

	/// 다시 받기
	if (false == fromClient->PostRecv())
	{
		fromClient->Disconnect();
		return;
	}
}
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// 에러 발생시 해당 세션 종료
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	fromClient->OnWriteComplete(cbTransferred);

}


///////////////////////////////////////////////////////////////////////////
/*
	보내기 완료한 패킷을 출력버퍼에서 제거하는 함수
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnWriteComplete(size_t len)
{
	mSendBuffer.Remove(len);
}

///////////////////////////////////////////////////////////////////////////
/*
	받은 패킷 파싱하여 처리하는 함수
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnRead(size_t len)
{
	mRecvBuffer.Commit(len);

	/// 패킷 파싱하고 처리
	while (true)
	{
		/// 패킷 헤더 크기 만큼 읽어와보기
		PacketHeader header;
		if (false == mRecvBuffer.Peek((char*)&header, sizeof(PacketHeader)))
			return;

		/// 패킷 완성이 되는가? 
		if (mRecvBuffer.GetStoredSize() < (size_t)header.mSize)
			return;


		if (header.mType >= PKT_MAX || header.mType <= PKT_NONE)
		{
			printf("[DEBUG] Invalid packet type \n");
			Disconnect();
			return;
		}

		/// packet dispatch...
		HandlerTable[header.mType](this);
	}
}

///////////////////////////////////////////////////////////////////////////
/*
	패킷 타입에 따라 파싱을 완료하고 작업을 처리하는 핸들러들
	*/
///////////////////////////////////////////////////////////////////////////
REGISTER_HANDLER(PKT_CS_LOGIN)
{
	LoginRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (!(GClientManager->IsValidPlayerId(inPacket.mPlayerId)))
	{
		printf("[DEBUG] playerId already exists\n");
		session->Disconnect();
		return;
	}
	session->LoginProcess(inPacket.mPlayerId);

	// 	LoadPlayerDataContext* newDbJob = new LoadPlayerDataContext(session->GetSocketKey(), inPacket.mPlayerId);
	// 	GDatabaseJobManager->PushDatabaseJobRequest(newDbJob);
}

REGISTER_HANDLER(PKT_CS_MAKE_ROOM)
{
	MakeRoomRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	session->MakeGameRoom();
}

REGISTER_HANDLER(PKT_CS_INOUT_ROOM)
{
	InOutRoomRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (session->GetPlayer()->GetPlayerID() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}

	if (inPacket.mIsIn)
	{
		session->JoinGameRoom();	
	}
	else
	{
		session->OutGameRoom();
	}
}

REGISTER_HANDLER(PKT_CS_GAME_READY)
{
	GameReadyNotify inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (session->GetPlayer()->GetPlayerID() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}

	auto player = session->GetPlayer();								_ASSERT(player != nullptr);
	auto room = GGameManager->SearchRoom(player->GetRoomID());		_ASSERT(room != nullptr);
	room->ReadySign();
	player->SetReady(true);
	player->SetHeroType(inPacket.mHeroType);
	printf(" - Player %d is Ready ! \n", inPacket.mPlayerId);

	if (room->IsAllReady())
	{
		session->AllReadyNotify();
	}
}

REGISTER_HANDLER(PKT_CS_RUN_COMPLETE)
{
	ClientRunCompleteNotify inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (session->GetPlayer()->GetPlayerID() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}

	auto player = session->GetPlayer();								_ASSERT(player != nullptr);
	auto game = GGameManager->SearchGame(player->GetRoomID());		_ASSERT(game != nullptr);
	game->SetLoadedPlayerNum();
}

REGISTER_HANDLER(PKT_CS_MOVE)
{
	MoveRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (session->GetPlayer()->GetPlayerID() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}
	printf(" Receive: LoginID: %d\t X : %.f\tY : %.f\n", inPacket.mPlayerId, inPacket.mTargetPos.x, inPacket.mTargetPos.y);

    b2Vec2 targetPos = DECREASE(inPacket.mTargetPos);
    b2Vec2 currentPos = DECREASE(inPacket.mCurrentPos);

	auto player = session->GetPlayer();								_ASSERT(player != nullptr);
	auto hero = player->GetMyHero();									_ASSERT(hero != nullptr);
	hero->TryMove(currentPos, targetPos);

	//session->SendUnitInfo(unit->GetUnitID(), unit->GetUnitType(), currentPos, targetPos);
}

REGISTER_HANDLER(PKT_CS_SKILL)
{
	SkillRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (session->GetPlayer()->GetPlayerID() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}
	printf(" SkillReceive: ID: %d\t\t X : %.f\tY : %.f\n", inPacket.mPlayerId, inPacket.mTargetPos.x, inPacket.mTargetPos.y);

    b2Vec2 targetPos = DECREASE(inPacket.mTargetPos);
    b2Vec2 currentPos = DECREASE(inPacket.mCurrentPos);

	auto player = session->GetPlayer();								_ASSERT(player != nullptr);
	auto hero = player->GetMyHero();									_ASSERT(hero != nullptr);
	hero->UseSkill(inPacket.mKey,currentPos, targetPos);

	//session->SendUnitInfo(unit->GetUnitID(), unit->GetUnitType(), currentPos, targetPos);
}

// 
// REGISTER_HANDLER(PKT_CS_CHAT)
// {
// 	ChatBroadcastRequest inPacket;
// 	if (false == session->ParsePacket(inPacket))
// 	{
// 		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
// 		return;
// 	}
// 
// 	if (inPacket.mPlayerId != session->GetPlayerId())
// 	{
// 		printf("[DEBUG] PKT_CS_CHAT: invalid player ID: %d \n", session->GetPlayerId());
// 		return;
// 	}
// 
// 	/// chatting의 경우 여기서 바로 방송
// 
// 	ChatBroadcastResult outPacket;
// 	outPacket.mPlayerId = inPacket.mPlayerId;
// 	strcpy_s(outPacket.mName, session->GetPlayerName());
// 	strcpy_s(outPacket.mChat, inPacket.mChat);
// 
// 	/// 채팅은 바로 방송 하면 끝
// 	if (!session->Broadcast(&outPacket))
// 	{
// 		session->Disconnect();
// 	}
// }







///////////////////////////////////////////////////////////////////////////
/*
	보낼 패킷 파싱하는 함수들
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::LoginProcess(int playerId)
{
	mPlayer = new Player(playerId);
	mLogon = true;

	LoginResult outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();
	strcpy_s(outPacket.mName, mPlayer->GetPlayerName());

	SendRequest(&outPacket);
	printf(" Send:   Login ID: %d \n", outPacket.mPlayerId);
}

void ClientSession::MakeGameRoom()
{
	GameRoom* gameRoom = GGameManager->CreateRoom();
	GGameManager->JoinRoom(gameRoom->GetRoomID(), mPlayer);

	MakeRoomResult outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();
	outPacket.mRoomId = gameRoom->GetRoomID();

	SendRequest(&outPacket);
	printf(" Send: Make Room ID: %d, Player ID: %d \n", outPacket.mRoomId, outPacket.mPlayerId);
}

void ClientSession::JoinGameRoom()
{
	auto roomId = GGameManager->SearchEmptyRoom();
	if (roomId < 0)
	{
		return;
	}
	GGameManager->JoinRoom(roomId, mPlayer);

	InOutRoomResult outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();
	outPacket.mRoomId = roomId;

	SendRequest(&outPacket);
	printf(" Send: Join Room ID: %d, Player ID: %d \n", outPacket.mRoomId, outPacket.mPlayerId);
}

void ClientSession::OutGameRoom()
{
	auto playerId = mPlayer->GetPlayerID();
	auto roomId = mPlayer->GetRoomID();
	if (playerId < 0 || roomId < 0)
	{
		return;
	}
	GGameManager->OutPlayer(roomId, playerId);

	printf(" Send:  Out Room ID: %d, Player ID: %d \n", roomId, playerId);
}

void ClientSession::ServerRunComplete()
{
	ServerRunCompleteNotify outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: ServerRunCompleteNotify Room ID: %d \n", mPlayer->GetRoomID());
}

void ClientSession::AllReadyNotify()
{
	GameRunNotify outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: GameRunNotify Room ID: %d \n", mPlayer->GetRoomID());
}

void ClientSession::SendCreateHeroResult(int unitId, HeroType unitType, b2Vec2 pos)
{
	CreateHeroResult outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();
	outPacket.mUnitId = unitId;
	outPacket.mUnitType = unitType;
	outPacket.mPos = INCREASE(pos);

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: CreateHeroResult Player ID: %d \n", mPlayer->GetPlayerID());
}

void ClientSession::StartGame()
{
	StartGameNotify outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: StartGameNotify Room ID: %d \n", mPlayer->GetRoomID());
}

void ClientSession::SendHeroInfo(int unitId, b2Vec2 currentPos, b2Vec2 targetPos)
{
	MoveBroadcastResult outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = INCREASE(currentPos);
    outPacket.mTargetPos = INCREASE(targetPos);

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}

void ClientSession::CrashedBroadCast(int unitId, UnitType unitType, b2Vec2 curPos, b2Vec2 expectPos, bool isCrashed)
{
	CrashedBroadcastResult outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();
	outPacket.mUnitId = unitId;
	outPacket.mUnitType = unitType;
    outPacket.mIsCrashed = isCrashed;
    outPacket.mCurrentPos = INCREASE(curPos);
    outPacket.mExpectPos = INCREASE(expectPos);

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	//printf(" Send: Crashed!  UnitID: %d, \t\t X : %.f\tY : %.f\n", unitId, outPacket.mExpectPosX, outPacket.mExpectPosY);
}

void ClientSession::SkillBroadCast(int heroId, SkillKey key, b2Vec2 currentPos, b2Vec2 targetPos)
{
	SkillBroadcastResult outPacket;
	outPacket.mPlayerId = mPlayer->GetPlayerID();
	outPacket.mUnitId = heroId;
    outPacket.mKey = key;
    outPacket.mCurrentPos = INCREASE(currentPos);
    outPacket.mTargetPos = INCREASE(targetPos);

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}

void ClientSession::MissileBroadCast(int playerId,int unitId, b2Vec2 currentPos, b2Vec2 targetPos)
{
	MissileBroadcastResult outPacket;
	outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = INCREASE(currentPos);
    outPacket.mTargetPos = INCREASE(targetPos);

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}

void ClientSession::TeleportBroadCast(int playerId, int unitId, b2Vec2 currentPos, b2Vec2 targetPos)
{
	TeleportBroadcastResult outPacket;
	outPacket.mPlayerId = playerId;
	outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = INCREASE(currentPos);
    outPacket.mTargetPos = INCREASE(targetPos);

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}

void ClientSession::HpBroadCast(int playerId, int unitId, UnitType unitType, int hp)
{
	HpBroadcastResult outPacket;
	outPacket.mPlayerId = playerId;
	outPacket.mUnitId = unitId;
	outPacket.mUnitType = unitType;
	outPacket.mHp = hp;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}