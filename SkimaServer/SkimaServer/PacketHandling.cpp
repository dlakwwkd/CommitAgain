#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Unit.h"
#include "Map.h"
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
    session->LoginProcess(inPacket.mPlayerId, inPacket.mPlayerName);

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
        session->JoinGameRoom(inPacket.mRoomId);	
    }
    else
    {
        session->OutGameRoom();
    }
}

REGISTER_HANDLER(PKT_CS_GAME_READY)
{
    GameReadyRequest inPacket;
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

    auto player = session->GetPlayer();								if (!player)    return;
    auto room = GGameManager->SearchRoom(player->GetRoomID());		if (!room)      return;
    room->ReadySign();
    player->SetReady(true);
    player->SetHeroType(inPacket.mHeroType);
    printf(" - Player %d is Ready ! \n", inPacket.mPlayerId);
    session->PlayerReadyNotify();

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

    auto player = session->GetPlayer();								if (!player)    return;
    auto game = GGameManager->SearchGame(player->GetRoomID());		if (!game)      return;
    game->SetLoadedPlayerNum();

    if (game->GetLoadedPlayerNum() >= MAX_PLAYER_NUM)
    {
        game->StartGame();
        session->SendStartGame();
    }
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
    printf(" Receive: LoginID: %d \t\t\t x : %.f \t y : %.f\n", inPacket.mPlayerId, inPacket.mTargetPos.x, inPacket.mTargetPos.y);

    auto player = session->GetPlayer();								if (!player)    return;
    auto hero = player->GetMyHero();									if (!hero)      return;
    auto roomId = player->GetRoomID();                              if (roomId < 0) return;

    b2Vec2 targetPos = CONVERT_IN(inPacket.mTargetPos, roomId);
    b2Vec2 currentPos = CONVERT_IN(inPacket.mCurrentPos, roomId);

    hero->StopSkill();
    hero->TryMove(currentPos, targetPos);
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
    printf(" SkillReceive: LoginID: %d \t\t\t x : %.f \t y : %.f\n", inPacket.mPlayerId, inPacket.mTargetPos.x, inPacket.mTargetPos.y);

    auto player = session->GetPlayer();								if (!player)    return;
    auto hero = player->GetMyHero();									if (!hero)      return;
    auto roomId = player->GetRoomID();                              if (roomId < 0) return;

    b2Vec2 targetPos = CONVERT_IN(inPacket.mTargetPos, roomId);
    b2Vec2 currentPos = CONVERT_IN(inPacket.mCurrentPos, roomId);

    hero->UseSkill(inPacket.mKey, currentPos, targetPos);
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
void ClientSession::LoginProcess(int playerId, const std::string& playerName)
{
    printf(" Recv:   Login Name: %s \n", playerName.c_str());
    mPlayer = new Player(this, playerId, playerName, PT_HUMAN);
    mLogon = true;

    int i = 0;
    auto roomList = GGameManager->GetRoomList();

    LoginResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    //RoomInfo 보내는 부분
    for (auto& room : roomList)
    {
        if (room.first <= 0) // 채워지지 않은 room이라면 break
            break;

        outPacket.mRoomList[i].mRoomNum = room.first;
        for (auto& player : room.second->GetPlayerList()) // room안에 player인원세기
            outPacket.mRoomList[i].mCurPlayerNum++;
        outPacket.mRoomList[i++].mMaxPlayerNum = MAX_PLAYER_NUM;
    }

    SendRequest(&outPacket);
    printf(" Send:   Login ID: %d \n", outPacket.mPlayerId);
}

void ClientSession::UpdateRoomInfo()
{
    int i = 0;
    auto roomList = GGameManager->GetRoomList();

    LoginResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();

    for (auto& room : roomList)
    {
        if (room.first <= 0) // 채워지지 않은 room이라면 break
            break;

        outPacket.mRoomList[i].mRoomNum = room.first;
        for (auto& player : room.second->GetPlayerList()) // room안에 player인원세기
            outPacket.mRoomList[i].mCurPlayerNum++;
        outPacket.mRoomList[i++].mMaxPlayerNum = MAX_PLAYER_NUM;
    }

    SendRequest(&outPacket);
    printf(" Send:   RoomInformation: roomMaxNum: %d, Player ID: %d \n", i, outPacket.mPlayerId);
}

void ClientSession::MakeGameRoom()
{
    GameRoom* gameRoom = GGameManager->CreateRoom();
    GGameManager->JoinRoom(gameRoom->GetRoomID(), mPlayer);

    MakeRoomResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mRoomId = mRoomId = gameRoom->GetRoomID();

    SendRequest(&outPacket);
    printf(" Send: Make Room ID: %d, Player ID: %d \n", outPacket.mRoomId, outPacket.mPlayerId);
}

void ClientSession::JoinGameRoom(int roomID)
{
    if (roomID < 0)
    {
        return;
    }
    GGameManager->JoinRoom(roomID, mPlayer);

    InOutRoomResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mRoomId = mRoomId = roomID;

    SendRequest(&outPacket);
    printf(" Send: Join Room ID: %d, Player ID: %d \n", outPacket.mRoomId, outPacket.mPlayerId);
}

void ClientSession::OutGameRoom()
{
    if (mPlayer == nullptr)
    {
        return;
    }
    GGameManager->PlayerOut(mPlayer);
}


///////////////////////////////////////////////////////////////////////////
/*
    로딩 처리 관련
*/
///////////////////////////////////////////////////////////////////////////

void ClientSession::PlayerReadyNotify()
{
    GameReadyResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    strcpy(outPacket.mPlayerName, mPlayer->GetPlayerName().c_str());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    printf(" Send: Player: %s is ready, Room ID: %d \n",mPlayer->GetPlayerName().c_str(), mPlayer->GetRoomID());
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

void ClientSession::SendCreateHeroResult(int unitId, const b2Vec2& pos)
{
    CreateHeroResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mPos = CONVERT_OUT(pos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    printf(" Send: CreateHeroResult Player ID: %d \n", mPlayer->GetPlayerID());
}

void ClientSession::SendMapInfo(int playerId, int unitId, const b2Vec2& pos)
{
    CreateMapResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mPos = CONVERT_OUT(pos, mPlayer->GetRoomID());

    printf("createPos x: %f y: %f\n", outPacket.mPos.x, outPacket.mPos.y);

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    printf(" Send: MapInfo Player ID: %d \n", mPlayer->GetPlayerID());
}

void ClientSession::SendStartGame()
{
    StartGameNotify outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    printf(" Send: StartGameNotify Room ID: %d \n", mPlayer->GetRoomID());
}


///////////////////////////////////////////////////////////////////////////
/*
    게임 플레이 관련
*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::TryMoveBroadCast(int unitId, const b2Vec2& curPos, const b2Vec2& targetPos)
{
    MoveBroadcastResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = CONVERT_OUT(curPos, mRoomId);
    outPacket.mTargetPos = CONVERT_OUT(targetPos, mRoomId);

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::CrashedBroadCast(int playerId, int unitId, const b2Vec2& curPos, const b2Vec2& expectPos, bool isCrashed)
{
    CrashedBroadcastResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mIsCrashed = isCrashed;
    outPacket.mCurrentPos = CONVERT_OUT(curPos, mRoomId);
    outPacket.mExpectPos = CONVERT_OUT(expectPos, mRoomId);

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::SkillBroadCast(int unitId, const b2Vec2& curPos, const b2Vec2& targetPos, SkillKey key)
{
    SkillBroadcastResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mKey = key;
    outPacket.mCurrentPos = CONVERT_OUT(curPos, mPlayer->GetRoomID());
    outPacket.mTargetPos = CONVERT_OUT(targetPos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::UnHideBroadCast(int unitId, const b2Vec2& curPos)
{
    UnHideBroadcastResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = CONVERT_OUT(curPos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::MeteorBroadCast(int unitId, const b2Vec2& targetPos)
{
    MeteorBroadcastResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mTargetPos = CONVERT_OUT(targetPos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::ShootBroadCast(int playerId,int unitId, const b2Vec2& curPos, const b2Vec2& targetPos)
{
    MissileBroadcastResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = CONVERT_OUT(curPos, mPlayer->GetRoomID());
    outPacket.mTargetPos = CONVERT_OUT(targetPos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::CreateMobBroadCast(int playerId, int unitId, const b2Vec2& pos)
{
    CreateMobResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mPos = CONVERT_OUT(pos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::HpBroadCast(int playerId, int unitId, int hp)
{
    HpBroadcastResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mHp = hp;

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::BuffBroadCast(int unitId, float bonus, BuffTarget type)
{
    BuffBroadcastResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mBonus = Extend(bonus);
    outPacket.mBuffTarget = type;
    
    printf(" - BuffBonus: %.f \n", outPacket.mBonus);

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::GameOverCast(int playerId)
{
    GameOverNotify outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mLoseId = playerId;

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}