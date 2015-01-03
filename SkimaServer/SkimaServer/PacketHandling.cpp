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
    if (!(GClientManager->IsValidPlayerName(inPacket.mPlayerName)))
    {
        printf("[DEBUG] playerName already exists\n");
        // 여기서 이미 로그인 되어 있음을 알려주는 패킷을 보내는 처리 해야함.
        session->Disconnect();
        return;
    }
    printf(" Recv:   Login Name: %s \n", inPacket.mPlayerName);
    session->LoginProcess(inPacket.mPlayerName);

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
    session->MakeGameRoom(inPacket.mRoomInfo);
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
        session->JoinGameRoom(inPacket.mRoomInfo);	
    }
    else
    {
        session->OutGameRoom(inPacket.mRoomInfo);
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
    player->SetTeam(inPacket.mTeam);
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

    if (game->GetLoadedPlayerNum() >= game->GetPlayerListSize() - 1)
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
    //printf(" Receive: LoginID: %d \t\t\t x : %.f \t y : %.f\n", inPacket.mPlayerId, inPacket.mTargetPos.x, inPacket.mTargetPos.y);

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
    //printf(" SkillReceive: LoginID: %d \t\t\t x : %.f \t y : %.f\n", inPacket.mPlayerId, inPacket.mTargetPos.x, inPacket.mTargetPos.y);

    auto player = session->GetPlayer();								if (!player)    return;
    auto hero = player->GetMyHero();									if (!hero)      return;
    auto roomId = player->GetRoomID();                              if (roomId < 0) return;

    b2Vec2 targetPos = CONVERT_IN(inPacket.mTargetPos, roomId);
    b2Vec2 currentPos = CONVERT_IN(inPacket.mCurrentPos, roomId);

    hero->UseSkill(inPacket.mKey, currentPos, targetPos);
}





///////////////////////////////////////////////////////////////////////////
/*
    보낼 패킷 파싱하는 함수들
*/
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/*
    로그인 및 대기실 관련
*/
///////////////////////////////////////////////////////////////////////////
void ClientSession::LoginProcess(const std::string& playerName)
{
    mPlayer = new Player(this, playerName, PT_HUMAN);
    mLogon = true;

    UpdateRoomInfo();
    printf(" Send:   Login ID: %d \n", mPlayer->GetPlayerID());
}

void ClientSession::UpdateRoomInfo()
{
    LoginResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();

    int i = 0;
    for (auto& room : GGameManager->GetRoomList())
    {
        if (room.first < 1) // invalid한 room은 skip
            continue;

        outPacket.mRoomList[i++] = room.second->GetRoomInfo();
    }

    SendRequest(&outPacket);
}

void ClientSession::MakeGameRoom(const RoomInfo& roomInfo)
{
    GameRoom* gameRoom = GGameManager->CreateRoom(roomInfo);
    GGameManager->JoinRoom(gameRoom->GetRoomID(), mPlayer);
    mRoomId = gameRoom->GetRoomID();

    auto roomList = GGameManager->GetRoomList();
    auto room = roomList.find(gameRoom->GetRoomID());
    if (room == roomList.end())
    {
        printf(" MakeGameRoom() Failed ! \n");
        return;
    }
    MakeRoomResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mRoomInfo.mRoomNum = mRoomId = gameRoom->GetRoomID();
    outPacket.mRoomInfo.mCurPlayerNum = 1; //방 생성한 player 1명
    outPacket.mRoomInfo.mMaxPlayerNum = roomInfo.mMaxPlayerNum;
    outPacket.mRoomInfo.mRoomType = roomInfo.mRoomType;
    outPacket.mRoomInfo.mIsStart = false;

    SendRequest(&outPacket);
    printf(" Send: Make Room ID: %d, Player ID: %d \n", outPacket.mRoomInfo.mRoomNum, outPacket.mPlayerId);
}

void ClientSession::JoinGameRoom(const RoomInfo& roomInfo)
{
    if (roomInfo.mRoomNum < 0)
    {
        return;
    }
    GGameManager->JoinRoom(roomInfo.mRoomNum, mPlayer);
    auto roomList = GGameManager->GetRoomList();
    auto room = roomList.find(roomInfo.mRoomNum);
    mRoomId = roomInfo.mRoomNum;

    if (room == roomList.end())
    {
        printf(" JoinGameRoom() Failed ! \n");
        return;
    }
    InOutRoomResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mRoomInfo = room->second->GetRoomInfo();
    outPacket.mIsIn = true;

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    printf(" Send: Out Room ID: %d, Player ID: %d \n CurPlayerNum: %d, MaxPlayerNum: %d\n",
        outPacket.mRoomInfo.mRoomNum, outPacket.mPlayerId, outPacket.mRoomInfo.mCurPlayerNum, outPacket.mRoomInfo.mMaxPlayerNum);
}

void ClientSession::OutGameRoom(const RoomInfo& roomInfo)
{
    if (mPlayer == nullptr)
    {
        return;
    }

    auto roomList = GGameManager->GetRoomList();
    auto room = roomList.find(roomInfo.mRoomNum);
    if (room == roomList.end())
    {
        printf(" OutGameRoom() Failed ! \n");
        return;
    }

    InOutRoomResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mRoomInfo = room->second->GetRoomInfo();
    outPacket.mRoomInfo.mCurPlayerNum--; //패킷을 보내고 playerOut을 해주어야 하기 때문에 보낼 패킷엔 임시로 -1을 해준다.
    outPacket.mIsIn = false;

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    GGameManager->PlayerOut(mPlayer);
    printf(" Send: Out Room ID: %d, Player ID: %d \n CurPlayerNum: %d, MaxPlayerNum: %d\n",
        outPacket.mRoomInfo.mRoomNum, outPacket.mPlayerId, outPacket.mRoomInfo.mCurPlayerNum, outPacket.mRoomInfo.mMaxPlayerNum);
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

void ClientSession::SendCreateHeroResult(int unitId, const b2Vec2& pos, RoomType roomType)
{
    CreateHeroResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mPos = CONVERT_OUT(pos, mPlayer->GetRoomID());
    outPacket.mTeam = mPlayer->GetTeam();
    outPacket.mRoomType = roomType;

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    //printf(" Send: CreateHeroResult Player ID: %d \n", mPlayer->GetPlayerID());
}

void ClientSession::SendMapInfo(int playerId, int unitId, const b2Vec2& pos)
{
    CreateMapResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mPos = CONVERT_OUT(pos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
    //printf(" Send: MapInfo Player ID: %d \t createPos  x: %.f \t y: %.f\n", mPlayer->GetPlayerID(), outPacket.mPos.x, outPacket.mPos.y);
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

void ClientSession::CrashedBroadCast(int playerId, int unitId, const b2Vec2& curPos, const b2Vec2& expectPos)
{
    CrashedBroadcastResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = CONVERT_OUT(curPos, mRoomId);
    outPacket.mExpectPos = CONVERT_OUT(expectPos, mRoomId);

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::SyncPosBroadCast(int playerId, int unitId, const b2Vec2& curPos)
{
    SyncPosBroadcastResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mCurrentPos = CONVERT_OUT(curPos, mRoomId);

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

void ClientSession::CreateMobBroadCast(int playerId, int unitId, const b2Vec2& pos, int hp, float speed)
{
    CreateMobResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mHp = hp;
    outPacket.mSpeed = Extend(speed);
    outPacket.mPos = CONVERT_OUT(pos, mPlayer->GetRoomID());

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::ItemBroadCast(int playerId, int unitId, const b2Vec2& pos, bool isCreate, BuffTarget buffType)
{
    ItemBroadcastResult outPacket;
    outPacket.mPlayerId = playerId;
    outPacket.mUnitId = unitId;
    outPacket.mIsCreate = isCreate;
    outPacket.mPos = CONVERT_OUT(pos, mPlayer->GetRoomID());
    outPacket.mBuffType = buffType;

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

void ClientSession::BuffBroadCast(int unitId, float bonus, BuffTarget type, bool isOn)
{
    BuffBroadcastResult outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mUnitId = unitId;
    outPacket.mBonus = Extend(bonus);
    outPacket.mBuffTarget = type;
    outPacket.mIsOn = isOn;
    
    //printf(" - BuffBonus: %.f \n", outPacket.mBonus);

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}

void ClientSession::GameOverCast(Team winTeam)
{
    GameOverNotify outPacket;
    outPacket.mPlayerId = mPlayer->GetPlayerID();
    outPacket.mWinTeam = winTeam;

    if (!Broadcast(&outPacket))
    {
        Disconnect();
    }
}