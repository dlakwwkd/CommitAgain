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
	printf("[DEBUG] Invalid packet handler \n", session->GetPlayerId());
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
	����� Ŭ���̾�Ʈ�� ��Ŷ �ް� ������ �۾� �Ϸ��ϴ� �ݹ� �Լ���
	*/
///////////////////////////////////////////////////////////////////////////
void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject;

	fromClient->DecRefCount();

	if (!fromClient->IsConnected())
		return;

	/// ���� �߻��� �ش� ���� ����
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	/// ���� ������ ó��
	fromClient->OnRead(cbTransferred);

	/// �ٽ� �ޱ�
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

	/// ���� �߻��� �ش� ���� ����
	if (dwError || cbTransferred == 0)
	{
		fromClient->Disconnect();
		return;
	}

	fromClient->OnWriteComplete(cbTransferred);

}


///////////////////////////////////////////////////////////////////////////
/*
	������ �Ϸ��� ��Ŷ�� ��¹��ۿ��� �����ϴ� �Լ�
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnWriteComplete(size_t len)
{
	mSendBuffer.Remove(len);
}

///////////////////////////////////////////////////////////////////////////
/*
	���� ��Ŷ �Ľ��Ͽ� ó���ϴ� �Լ�
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::OnRead(size_t len)
{
	mRecvBuffer.Commit(len);

	/// ��Ŷ �Ľ��ϰ� ó��
	while (true)
	{
		/// ��Ŷ ��� ũ�� ��ŭ �о�ͺ���
		PacketHeader header;
		if (false == mRecvBuffer.Peek((char*)&header, sizeof(PacketHeader)))
			return;

		/// ��Ŷ �ϼ��� �Ǵ°�? 
		if (mRecvBuffer.GetStoredSize() < (size_t)header.mSize)
			return;


		if (header.mType >= PKT_MAX || header.mType <= PKT_NONE)
		{
			printf("[DEBUG] Invalid packet type \n", GetPlayerId());
			Disconnect();
			return;
		}

		/// packet dispatch...
		HandlerTable[header.mType](this);
	}
}

///////////////////////////////////////////////////////////////////////////
/*
	��Ŷ Ÿ�Կ� ���� �Ľ��� �Ϸ��ϰ� �۾��� ó���ϴ� �ڵ鷯��
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
	session->LoginSuccessInform(inPacket.mPlayerId);

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
	session->MakeGameRoom(inPacket.mPlayerId);
}

REGISTER_HANDLER(PKT_CS_INOUT_ROOM)
{
	InOutRoomRequest inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (session->GetPlayerId() != inPacket.mPlayerId)
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
	if (session->GetPlayerId() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}
	printf(" - Player %d is Ready ! \n", inPacket.mPlayerId);

	auto room = GGameManager->SearchRoom(session->GetRoomId());			_ASSERT(room != nullptr);
	room->ReadySign();
	session->SetReady();

	if (room->IsAllReady())
	{
		session->AllReadyNotify();
	}

	session->
}

REGISTER_HANDLER(PKT_CS_RUN_COMPLETE)
{
	ClientRunCompleteNotify inPacket;
	if (false == session->ParsePacket(inPacket))
	{
		printf("[DEBUG] packet parsing error: %d \n", inPacket.mType);
		return;
	}
	if (session->GetPlayerId() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}
	auto game = GGameManager->SearchGame(session->GetPlayerId());		_ASSERT(game != nullptr);
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
	if (session->GetPlayerId() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}
	printf(" Receive: LoginID: %d\t\t X : %.f\tY : %.f\n", session->GetPlayerId(), inPacket.mTargetPosX, inPacket.mTargetPosY);

	b2Vec2 targetPos;
	b2Vec2 currentPos;
	targetPos.x = inPacket.mTargetPosX / PTM_RATIO;
	targetPos.y = inPacket.mTargetPosY / PTM_RATIO;
	currentPos.x = inPacket.mCurrentPosX / PTM_RATIO;
	currentPos.y = inPacket.mCurrentPosY / PTM_RATIO;

	auto player = GGameManager->SearchPlayer(session->GetPlayerId());	_ASSERT(player != nullptr);
	auto hero = player->GetMyHero();										_ASSERT(hero != nullptr);
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
	if (session->GetPlayerId() != inPacket.mPlayerId)
	{
		printf("[DEBUG] Player Info error! \n");
		return;
	}
	printf(" SkillReceive: LoginID: %d\t\t X : %.f\tY : %.f\n", session->GetPlayerId(), inPacket.mTargetPosX, inPacket.mTargetPosY);

	b2Vec2 targetPos;
	b2Vec2 currentPos;
	targetPos.x = inPacket.mTargetPosX / PTM_RATIO;
	targetPos.y = inPacket.mTargetPosY / PTM_RATIO;
	currentPos.x = inPacket.mCurrentPosX / PTM_RATIO;
	currentPos.y = inPacket.mCurrentPosY / PTM_RATIO;

	auto player = GGameManager->SearchPlayer(session->GetPlayerId());	_ASSERT(player != nullptr);
	auto hero = player->GetMyHero();										_ASSERT(hero != nullptr);
	hero->UseSkill(inPacket.mKey, targetPos);

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
// 	/// chatting�� ��� ���⼭ �ٷ� ���
// 
// 	ChatBroadcastResult outPacket;
// 	outPacket.mPlayerId = inPacket.mPlayerId;
// 	strcpy_s(outPacket.mName, session->GetPlayerName());
// 	strcpy_s(outPacket.mChat, inPacket.mChat);
// 
// 	/// ä���� �ٷ� ��� �ϸ� ��
// 	if (!session->Broadcast(&outPacket))
// 	{
// 		session->Disconnect();
// 	}
// }







///////////////////////////////////////////////////////////////////////////
/*
	���� ��Ŷ �Ľ��ϴ� �Լ���
	*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::LoginSuccessInform(int id)
{
	LoginResult outPacket;
	outPacket.mPlayerId = mPlayerId = id;
	// ���⼭�� �ϴ� ID�� �г����� �����µ�,
	// ���߿� DB�� �̿��� ID���� �г����� �����ؾ� �ҵ�. -����
	itoa(mPlayerId, mPlayerName, 10);
	strcpy_s(outPacket.mName, mPlayerName);

	mLogon = true;
	SendRequest(&outPacket);
	printf(" Send:   Login ID: %d \n", outPacket.mPlayerId);
}

void ClientSession::MakeGameRoom(int id)
{
	GameRoom* gameRoom = GGameManager->CreateRoom();
	GGameManager->JoinRoom(id, gameRoom->GetRoomID());

	MakeRoomResult outPacket;
	outPacket.mPlayerId = mPlayerId = id;
	outPacket.mRoomId = mRoomId = gameRoom->GetRoomID();

	SendRequest(&outPacket);
	printf(" Send: Make Room ID: %d, Player ID: %d \n", outPacket.mRoomId, outPacket.mPlayerId);
}

void ClientSession::JoinGameRoom()
{
	auto roomNum = GGameManager->SearchEmptyRoom();
	if (roomNum < 0)
	{
		return;
	}
	GGameManager->JoinRoom(mPlayerId, roomNum);

	InOutRoomResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mRoomId = mRoomId = roomNum;

	SendRequest(&outPacket);
	printf(" Send: Join Room ID: %d, Player ID: %d \n", outPacket.mRoomId, outPacket.mPlayerId);
}

void ClientSession::OutGameRoom()
{
	if(mRoomId < 0 || mPlayerId < 0)
		return;
	GGameManager->OutRoom(mPlayerId, mRoomId);

	mRoomId = -1;
	mIsReady = false;
	printf(" Send:  Out Room ID: %d, Player ID: %d \n", mRoomId, mPlayerId);
}

void ClientSession::ServerRunComplete()
{
	ServerRunCompleteNotify outPacket;
	outPacket.mPlayerId = mPlayerId;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: ServerRunCompleteNotify Room ID: %d \n", mRoomId);
}

void ClientSession::AllReadyNotify()
{
	GameRunNotify outPacket;
	outPacket.mPlayerId = mPlayerId;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: GameRunNotify Room ID: %d \n", mRoomId);
}

void ClientSession::SendCreateHeroResult(int unitId, HeroType unitType, b2Vec2 pos)
{
	CreateHeroResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mUnitId = unitId;
	outPacket.mUnitType = unitType;
	outPacket.mPosX = pos.x*PTM_RATIO;
	outPacket.mPosY = pos.y*PTM_RATIO;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: CreateHeroResult Player ID: %d \n", mPlayerId);
}

void ClientSession::StartGame()
{
	StartGameNotify outPacket;
	outPacket.mPlayerId = mPlayerId;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: StartGameNotify Room ID: %d \n", mRoomId);
}

void ClientSession::SendHeroInfo(int unitId, b2Vec2 currentPos, b2Vec2 targetPos)
{
	MoveBroadcastResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mUnitId = unitId;
	outPacket.mCurrentPosX = currentPos.x*PTM_RATIO;
	outPacket.mCurrentPosY = currentPos.y*PTM_RATIO;
	outPacket.mTargetPosX = targetPos.x*PTM_RATIO;
	outPacket.mTargetPosY = targetPos.y*PTM_RATIO;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}

void ClientSession::CrashedBroadCast(int unitId, b2Vec2 currentPos, b2Vec2 expectPos, bool isCrashed)
{
	CrashedBroadcastResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mUnitId = unitId;
	outPacket.mIsCrashed = isCrashed;
	outPacket.mCurrentPosX = currentPos.x * PTM_RATIO;
	outPacket.mCurrentPosY = currentPos.y * PTM_RATIO;
	outPacket.mExpectPosX = expectPos.x*PTM_RATIO;
	outPacket.mExpectPosY = expectPos.y*PTM_RATIO;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
	printf(" Send: Crashed!  UnitID: %d, \t\t X : %.f\tY : %.f\n", unitId, outPacket.mExpectPosX, outPacket.mExpectPosY);
}

void ClientSession::SkillBroadCast(int heroId, SkillKey key, b2Vec2 currentPos, b2Vec2 targetPos)
{
	SkillBroadcastResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mHeroId = heroId;
	outPacket.mKey = key;
	outPacket.mCurrentPosX = currentPos.x*PTM_RATIO;
	outPacket.mCurrentPosY = currentPos.y*PTM_RATIO;
	outPacket.mTargetPosX = targetPos.x*PTM_RATIO;
	outPacket.mTargetPosY = targetPos.y*PTM_RATIO;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}

void ClientSession::MissileBroadCast(int unitId, b2Vec2 currentPos, b2Vec2 targetPos)
{
	MissileBroadcastResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mUnitId = unitId;
	outPacket.mCurrentPosX = currentPos.x*PTM_RATIO;
	outPacket.mCurrentPosY = currentPos.y*PTM_RATIO;
	outPacket.mTargetPosX = targetPos.x*PTM_RATIO;
	outPacket.mTargetPosY = targetPos.y*PTM_RATIO;

	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}