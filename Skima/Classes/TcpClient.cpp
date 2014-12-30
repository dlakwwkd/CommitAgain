#include "pch.h"
#include <thread>
#include "TcpClient.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "2d/CCLabel.h"
#include "PacketType.h"
#include "GameScene.h"
#include "NetworkScene.h"
#include "RoomScene.h"
#include "ObjectLayer.h"
#include "LoadingBGLayer.h"
#include "Enums.h"
#include "Macros.h"
#include "MapLayer.h"

#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#define sleep(x) Sleep(x)
#endif

static TcpClient* s_TcpClient = nullptr;

TcpClient::TcpClient() : mRecvBuffer(BUF_SIZE), mSock(NULL), mLoginId(-1)
{
}

TcpClient::~TcpClient()
{
    disconnect();
}

TcpClient* TcpClient::getInstance()
{
    if (nullptr == s_TcpClient)
    {
        s_TcpClient = new TcpClient();
    }
    return s_TcpClient;
}

void TcpClient::destroyInstance()
{
    CC_SAFE_DELETE(s_TcpClient);
}




///////////////////////////////////////////////////////////////////////////
/*
    서버와의 연결, 연결해제 함수
*/
///////////////////////////////////////////////////////////////////////////
bool TcpClient::connect()
{
    if (mSock != NULL)
    {
        TcpClient::getInstance()->disconnect();
    }
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return false;
#endif

    mSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mSock == INVALID_SOCKET)
        return false;

    std::string ipaddr = cocos2d::UserDefault::getInstance()->getStringForKey("ipaddr", std::string("localhost"));
    int port = cocos2d::UserDefault::getInstance()->getIntegerForKey("port", 9001);

    struct hostent* host;
    struct sockaddr_in hostAddr;

    if ((host = gethostbyname(ipaddr.c_str())) == 0)
        return false;

    ZeroMemory(&hostAddr, sizeof(hostAddr));
    hostAddr.sin_family = AF_INET;
    hostAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    hostAddr.sin_port = htons(port);

    if (SOCKET_ERROR == ::connect(mSock, (struct sockaddr*)&hostAddr, sizeof(hostAddr)))
    {
        CCLOG("CONNECT FAILED");
        return false;
    }

    /// nagle 알고리즘 끄기
    int opt = 1;
    setsockopt(mSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int));

    /// 쓰레드 생성
    auto t = std::thread(CC_CALLBACK_0(TcpClient::networkThread, this));
    t.detach();

    return true;
}

void TcpClient::disconnect()
{
    if (mSock == NULL)
        return;

#ifdef _WIN32
    closesocket(mSock);
    WSACleanup();
#else
    close(mSock);
#endif

    mSock = NULL;
    mLoginId = -1;

    return;
}


///////////////////////////////////////////////////////////////////////////
/*
    실제 패킷을 보내고, 받는 함수
*/
///////////////////////////////////////////////////////////////////////////
bool TcpClient::send(const char* data, int length)
{
    int count = 0;
    while (count < length) 
    {
        int n = ::send(mSock, data + count, length, 0);
        if (n == SOCKET_ERROR)
        {
            CCLOG("SEND ERROR");
            return false;
        }
        count += n;
        length -= n;
    }

    return true;
}

void TcpClient::networkThread()
{
    while (mSock) 
    {
        char inBuf[4096] = { 0, };

        int n = ::recv(mSock, inBuf, 4096, 0);

        if (n < 1)
        {
            disconnect();
            return;
        }

        if (!mRecvBuffer.Write(inBuf, n))
        {
            /// 버퍼 꽉찼다. 
            assert(false);
        }

        processPacket();
    }
}


///////////////////////////////////////////////////////////////////////////
/*
    받은 패킷 파싱하여 처리하는 함수
*/
///////////////////////////////////////////////////////////////////////////
void TcpClient::processPacket()
{
    auto scheduler = cocos2d::Director::getInstance()->getScheduler();

    /// 패킷을 파싱해서 완성되는 패킷이 있으면, 해당 콜백을 불러준다. 
    while (true)
    {
        PacketHeader header;

        if (false == mRecvBuffer.Peek((char*)&header, sizeof(PacketHeader)))
            break;

        if (header.mSize > mRecvBuffer.GetStoredSize())
            break;
        
        if (cocos2d::Director::getInstance()->getRunningScene() == nullptr)
            break;

        switch (header.mType)
        {
        case PKT_SC_LOGIN:
        {
            LoginResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            mLoginId = recvData.mPlayerId;

            auto scene = GET_NETWORK_SCENE;
            if (scene)
            {
                //다음 update를 위한 초기화
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::ClearRoomInfo, scene));
                for (auto& room : recvData.mRoomList)
                {
                    if (room.mRoomNum <= 0) // roomNum이 0이하면 roomList의 끝이므로 break
                        break;
                    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::RoomInformation, scene,
                        room));
                }
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::UpdateRoomInfo, scene));
            }
        }
        break;

        case PKT_SC_MAKE_ROOM:
        {
            MakeRoomResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId == mLoginId);

            auto scene = GET_NETWORK_SCENE;
            if (scene)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::MakeRoomComplete, scene,
                    recvData.mRoomInfo));
            }
        }
        break;

        case PKT_SC_INOUT_ROOM:
        {
            InOutRoomResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            if (recvData.mPlayerId != mLoginId)
            {
                auto scene = GET_ROOM_SCENE;
                if (scene)
                {
                    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(RoomScene::UpdateRoomInfo, scene,
                        recvData.mRoomInfo));
                }
            }
            else
            {
                auto scene = GET_NETWORK_SCENE;
                if (scene)
                {
                    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::JoinRoomComplete, scene,
                        recvData.mRoomInfo));
                }
            }
        }
        break;

        case PKT_SC_GAME_READY:
        {
            GameReadyResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            auto scene = GET_ROOM_SCENE;
        }
        break;

        case PKT_SC_ALL_READY:
        {
            GameRunNotify recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            auto scene = GET_ROOM_SCENE;
            if (scene)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(RoomScene::GameStart, scene));
            }
        }
        return; // 이 다음 패킷 수신 전에 콜백함수 호출이 필요하므로 리턴

        case PKT_SC_CREATE_HERO:
        {
            CreateHeroResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 pos = CONVERT(recvData.mPos);
            mTeam = recvData.mTeam;

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::CreateHero, layer,
                    recvData.mPlayerId, recvData.mUnitId, pos, recvData.mTeam, recvData.mRoomType));
            }
        }
        break;

        case PKT_SC_CREATE_MAP:
        {
            CreateMapResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 pos = CONVERT(recvData.mPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::CreateMapObject, layer,
                    recvData.mUnitId, pos));
            }
        }
        break;
        
        case PKT_SC_CREATE_MOB:
        {
            CreateMobResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 pos = CONVERT(recvData.mPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::CreateMob, layer,
                    recvData.mPlayerId, recvData.mUnitId, pos, recvData.mHp, recvData.mSpeed));
            }
        }
        break;
        
        case PKT_SC_CREATE_ITEM:
        {
            ItemBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 pos = CONVERT(recvData.mPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                if (recvData.mIsCreate)
                {
                    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::CreateItem, layer,
                        recvData.mPlayerId, recvData.mUnitId, pos, recvData.mBuffType));
                }
                else
                {
                    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::RemoveItem, layer,
                        recvData.mPlayerId, recvData.mUnitId));
                }
            }
        }
        break;

        case PKT_SC_RUN_COMPLETE:
        {
            ServerRunCompleteNotify recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_LOADING_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(LoadingBGLayer::SetLoadingFin, layer));
            }
        }
        return; // 이 다음 패킷 수신 전에 콜백함수 호출이 필요하므로 리턴

        case PKT_SC_START_GAME:
        {	
            StartGameNotify recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            auto scene = GET_GAME_SCENE;
            if (scene)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(GameScene::StartGame, scene));
            }
        }
        break;

        case PKT_SC_MOVE:
        {
            MoveBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);
            
            Vec2 curPos = CONVERT(recvData.mCurrentPos);
            Vec2 targetPos = CONVERT(recvData.mTargetPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitMove, layer,
                    recvData.mUnitId, curPos, targetPos));
            }
        }
        break;

        case PKT_SC_CRASH:
        {
            CrashedBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 expectPos = CONVERT(recvData.mExpectPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitCrash, layer,
                    recvData.mUnitId, expectPos));
            }
        }
        break;
        
        case PKT_SC_SYNC:
        {
            SyncPosBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 revisionPos = CONVERT(recvData.mCurrentPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitCrashEnd, layer,
                    recvData.mUnitId, revisionPos));

                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::MissileCrash, layer,
                    recvData.mUnitId));
            }
        }
        break;

        case PKT_SC_SKILL:
        {
            SkillBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 curPos = CONVERT(recvData.mCurrentPos);
            Vec2 targetPos = CONVERT(recvData.mTargetPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitSkillUse, layer,
                    recvData.mPlayerId, recvData.mUnitId, recvData.mKey, curPos, targetPos));
            }
        }
        break;

        case PKT_SC_MISSILE:
        {
            MissileBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 curPos = CONVERT(recvData.mCurrentPos);
            Vec2 targetPos = CONVERT(recvData.mTargetPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::ShootMissile, layer,
                    recvData.mUnitId, curPos, targetPos));
            }
        }
        break;

        case PKT_SC_HP:
        {
            HpBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitHpUpdate, layer,
                    recvData.mPlayerId, recvData.mUnitId, recvData.mHp));
            }
        }
        break;
        
        case PKT_SC_BUFF:
        {
            BuffBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitBuffApply, layer,
                    recvData.mUnitId, recvData.mBonus, recvData.mBuffTarget, recvData.mIsOn));
            }
        }
        break;

        case PKT_SC_UNHIDE:
        {
            UnHideBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 curPos = CONVERT(recvData.mCurrentPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnHide, layer,
                    recvData.mPlayerId, recvData.mUnitId, curPos));
            }
        }
        break;

        case PKT_SC_METEOR:
        {
            MeteorBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            Vec2 targetPos = CONVERT(recvData.mTargetPos);

            if (GET_GAME_SCENE == nullptr)
            {
                break;
            }
            auto layer = GET_OBJECT_LAYER;
            if (layer)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::MeteorCreate, layer,
                    recvData.mPlayerId, recvData.mUnitId, targetPos));
            }
        }
            break;

        case PKT_SC_GAMEOVER:
        {
            GameOverNotify recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            bool isWin = false;
            if (mTeam == recvData.mWinTeam)
            {
                isWin = true;
            }

            auto scene = GET_GAME_SCENE;
            if (scene)
            {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(GameScene::GameOver, scene,
                    mLoginId, isWin));
            }
        }
        return;

        default:
            assert(false);
        }

    }
}


///////////////////////////////////////////////////////////////////////////
/*
    보낼 패킷 파싱하는 함수들
*/
///////////////////////////////////////////////////////////////////////////
void TcpClient::loginRequest(const char* playerName)
{
    if (mLoginId > 0)
        return;

    srand(time(NULL));

    LoginRequest sendData;
    sendData.mPlayerId = 1000 + rand() % 101;	// 아이디 임시로 랜덤 생성
    strcpy(sendData.mPlayerName, playerName);
    strcpy(mLoginName, playerName);

    send((const char*)&sendData, sizeof(LoginRequest));
}

void TcpClient::makeRoomRequest(RoomInfo roomInfo)
{
    if (mLoginId < 0)
        return;

    MakeRoomRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mRoomInfo = roomInfo;

    send((const char*)&sendData, sizeof(MakeRoomRequest));
}

void TcpClient::joinRoomRequest(RoomInfo roomInfo)
{
    if (mLoginId < 0)
        return;

    InOutRoomRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mIsIn = true;
    sendData.mRoomInfo = roomInfo;

    send((const char*)&sendData, sizeof(InOutRoomRequest));
}

void TcpClient::outRoomRequest(RoomInfo roomInfo)
{
    if (mLoginId < 0)
        return;

    InOutRoomRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mIsIn = false;
    sendData.mRoomInfo = roomInfo;

    send((const char*)&sendData, sizeof(InOutRoomRequest));
}

void TcpClient::startGameRequest(int roomId, Team team, HeroType heroType)
{
    if (mLoginId < 0)
        return;
    mTeam = team;

    GameReadyRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mTeam = team;
    sendData.mHeroType = heroType;

    send((const char*)&sendData, sizeof(GameReadyRequest));
}

void TcpClient::runCompleteRequest()
{
    if (mLoginId < 0)
        return;

    ClientRunCompleteNotify sendData;
    sendData.mPlayerId = mLoginId;

    send((const char*)&sendData, sizeof(ClientRunCompleteNotify));
}

void TcpClient::moveRequest(Vec2 curPos, Vec2 targetPos)
{
    if (mLoginId < 0)
        return;

    MoveRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mCurrentPos = CONVERT(curPos);
    sendData.mTargetPos = CONVERT(targetPos);

    send((const char*)&sendData, sizeof(MoveRequest));
}

void TcpClient::skillRequest(Vec2 curPos, Vec2 targetPos, SkillKey skillKey)
{
    if (mLoginId < 0)
        return;

    SkillRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mCurrentPos = CONVERT(curPos);
    sendData.mTargetPos = CONVERT(targetPos);
    sendData.mKey = skillKey;

    send((const char*)&sendData, sizeof(SkillRequest));
}

