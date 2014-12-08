#include "pch.h"
#include <thread>
#include "TcpClient.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "2d/CCLabel.h"
#include "PacketType.h"
#include "SingleGameScene.h"
#include "MultiGameScene.h"
#include "NetworkScene.h"
#include "RoomScene.h"
#include "ObjectLayer.h"
#include "LoadingBGLayer.h"
#include "Enums.h"

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

        switch (header.mType)
        {
        case PKT_SC_LOGIN:
            {
                LoginResult recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);
    
                mLoginId = recvData.mPlayerId;

                auto scene = GET_NETWORK_SCENE;     assert(scene != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::ConnectLabelChange, scene,
                    "서버 접속 성공!!"));
            }
            break;

        case PKT_SC_MAKE_ROOM:
            {
                MakeRoomResult recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId == mLoginId);

                auto scene = GET_NETWORK_SCENE;     assert(scene != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::MakeRoomComplete, scene,
                    recvData.mRoomId));
            }
            break;

        case PKT_SC_INOUT_ROOM:
            {
                InOutRoomResult recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId == mLoginId);

                if (recvData.mIsIn)
                {
                    auto scene = GET_NETWORK_SCENE; assert(scene != nullptr);
                    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::JoinRoomComplete, scene,
                        recvData.mRoomId));
                }
                else
                {
                    //나간 플레이어 처리 필요
                }
            }
            break;

        case PKT_SC_ALL_READY:
            {
                GameRunNotify recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);

                auto scene = GET_ROOM_SCENE;        assert(scene != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(RoomScene::GameStartComplete, scene));
            }
            return; // 이 다음 패킷 수신 전에 콜백함수 호출이 필요하므로 리턴

        case PKT_SC_CREATE_HERO:
            {
                CreateHeroResult recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);

                Vec2 pos = CONVERT(recvData.mPos);

                auto layer = GET_OBJECT_LAYER;      assert(layer != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::FirstDrawUnit, layer,
                    recvData.mPlayerId, recvData.mUnitId, pos));
            }
            break;

        case PKT_SC_RUN_COMPLETE:
            {
                ServerRunCompleteNotify recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);

                auto layer = GET_LOADING_LAYER;     assert(layer != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(LoadingBGLayer::SetLoadingFin, layer));
            }
            return; // 이 다음 패킷 수신 전에 콜백함수 호출이 필요하므로 리턴

        case PKT_SC_START_GAME:
            {	
                StartGameNotify recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);

                auto scene = GET_M_GAME_SCENE;      assert(scene != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(MultiGameScene::StartGame, scene));
            }
            break;

        case PKT_SC_MOVE:
            {
                MoveBroadcastResult recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);
                
                Vec2 curPos = CONVERT(recvData.mCurrentPos);
                Vec2 targetPos = CONVERT(recvData.mTargetPos);

                auto layer = GET_OBJECT_LAYER;      assert(layer != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitMove, layer,
                    recvData.mUnitId, curPos, targetPos));
            }
            break;

        case PKT_SC_CRASH:
            {
                CrashedBroadcastResult recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);

                Vec2 expectPos = CONVERT(recvData.mExpectPos);
                Vec2 revisionPos = CONVERT(recvData.mCurrentPos);

                auto layer = GET_OBJECT_LAYER;      assert(layer != nullptr);
                switch (GET_MAIN_TYPE(recvData.mUnitId))
                {
                case UNIT_HERO:
                    if (recvData.mIsCrashed)
                    {
                        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitCrash, layer,
                            recvData.mUnitId, expectPos));
                    }
                    else
                    {
                        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitCrashEnd, layer,
                            recvData.mUnitId, revisionPos));
                    }
                    break;
                case UNIT_MISSILE:
                    scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::MissileCrash, layer,
                        recvData.mUnitId));
                    break;
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

                auto layer = GET_OBJECT_LAYER;      assert(layer != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitSkillUse, layer,
                    recvData.mUnitId, recvData.mSkillType, recvData.mKey, curPos, targetPos));
            }
            break;
        case PKT_SC_MISSILE:
            {
                MissileBroadcastResult recvData;
                bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
                assert(ret && recvData.mPlayerId != -1);

                Vec2 curPos = CONVERT(recvData.mCurrentPos);
                Vec2 targetPos = CONVERT(recvData.mTargetPos);

                auto layer = GET_OBJECT_LAYER;      assert(layer != nullptr);
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::ShootMissile, layer,
                    recvData.mUnitId, curPos, targetPos));
            }
            break;
        case PKT_SC_HP:
        {
            HpBroadcastResult recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            auto layer = GET_OBJECT_LAYER;          assert(layer != nullptr);
            scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitHpUpdate, layer,
                recvData.mPlayerId, recvData.mUnitId, recvData.mHp));
        }
        break;

        case  PKT_SC_GAMEOVER:
        {
            GameOverNotify recvData;
            bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
            assert(ret && recvData.mPlayerId != -1);

            GameResult result;

            auto scene = GET_M_GAME_SCENE;          assert(scene != nullptr);
            scheduler->performFunctionInCocosThread(CC_CALLBACK_0(MultiGameScene::GameOver, scene, mLoginId, recvData.mLoseId));
        }
            break;

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
void TcpClient::loginRequest()
{
    if (mLoginId > 0)
        return;

    srand(time(NULL));

    LoginRequest sendData;
    sendData.mPlayerId = 1000 + rand() % 101;	// 아이디 임시로 랜덤 생성

    send((const char*)&sendData, sizeof(LoginRequest));
}

void TcpClient::makeRoomRequest()
{
    if (mLoginId < 0)
        return;

    MakeRoomRequest sendData;
    sendData.mPlayerId = mLoginId;

    send((const char*)&sendData, sizeof(MakeRoomRequest));
}

void TcpClient::joinRoomRequest()
{
    if (mLoginId < 0)
        return;

    InOutRoomRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mIsIn = true;

    send((const char*)&sendData, sizeof(InOutRoomRequest));
}

void TcpClient::outRoomRequest(int roomId)
{
    if (mLoginId < 0)
        return;

    InOutRoomRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mIsIn = false;
    sendData.mRoomId = roomId;

    send((const char*)&sendData, sizeof(InOutRoomRequest));
}

void TcpClient::startGameRequest(int roomId,HeroType heroType)
{
    if (mLoginId < 0)
        return;

    GameReadyNotify sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mHeroType = heroType; 

    send((const char*)&sendData, sizeof(GameReadyNotify));
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

void TcpClient::skillRequest(Vec2 curPos, Vec2 targetPos, SkillType skillType, SkillKey skillKey)
{
    if (mLoginId < 0)
        return;

    SkillRequest sendData;
    sendData.mPlayerId = mLoginId;
    sendData.mCurrentPos = CONVERT(curPos);
    sendData.mTargetPos = CONVERT(targetPos);
    sendData.mSkillType = skillType;
    sendData.mKey = skillKey;

    send((const char*)&sendData, sizeof(SkillRequest));
}












//  void TcpClient::chatRequest(const char* chat)
//  {
// 	 if (mLoginId < 0)
// 		 return;
// 
// 	 ChatBroadcastRequest sendData;
// 
// 	 sendData.mPlayerId = mLoginId;
// 	 memcpy(sendData.mChat, chat, strlen(chat));
// 
// 	 send((const char*)&sendData, sizeof(ChatBroadcastRequest));
//  }
// 
