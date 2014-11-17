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

#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#define sleep(x) Sleep(x)
#endif

static TcpClient* s_TcpClient = nullptr;

TcpClient::TcpClient() : mRecvBuffer(BUF_SIZE), mSock(NULL), mLoginId(-1)
{
	/// ������ ����
	auto t = std::thread(CC_CALLBACK_0(TcpClient::networkThread, this));
	t.detach();
}

TcpClient::~TcpClient()
{
	if(mSock == NULL)
		return;

#ifndef _WIN32
	close(mSock);
#else
	closesocket(mSock);
	WSACleanup();
#endif
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
	�������� ����, �������� �Լ�
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

	memset(&hostAddr, 0, sizeof(hostAddr));
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	hostAddr.sin_port = htons(port);

	if (SOCKET_ERROR == ::connect(mSock, (struct sockaddr*)&hostAddr, sizeof(hostAddr)))
	{
		CCLOG("CONNECT FAILED");
		return false;
	}

	/// nagle �˰��� ����
	int opt = 1;
	setsockopt(mSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int));

	return true;
}

void TcpClient::disconnect()
{
	if (mSock == NULL)
		return;

#ifndef _WIN32
	close(mSock);
#else
	closesocket(mSock);
	WSACleanup();
#endif
	mSock = NULL;
	mLoginId = -1;

	return;
}


///////////////////////////////////////////////////////////////////////////
/*
	���� ��Ŷ�� ������, �޴� �Լ�
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
	while ( true ) 
	{
		char inBuf[4096] = { 0, };

		int n = ::recv(mSock, inBuf, 4096, 0);

		if (n < 1)
		{
			sleep(0); ///< for cpu low-utilization
			continue;
		}

		if (!mRecvBuffer.Write(inBuf, n))
		{
			/// ���� ��á��. 
			assert(false);
		}

		processPacket();
	}
}


///////////////////////////////////////////////////////////////////////////
/*
	���� ��Ŷ �Ľ��Ͽ� ó���ϴ� �Լ�
*/
///////////////////////////////////////////////////////////////////////////
void TcpClient::processPacket()
{
	auto scheduler = cocos2d::Director::getInstance()->getScheduler();

	/// ��Ŷ�� �Ľ��ؼ� �ϼ��Ǵ� ��Ŷ�� ������, �ش� �ݹ��� �ҷ��ش�. 
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

				auto scene = GET_NETWORK_SCENE;		assert(scene != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::ConnectLabelChange, scene,
					"���� ���� ����!!"));
			}
			break;

		case PKT_SC_MAKE_ROOM:
			{
				MakeRoomResult recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId == mLoginId);

				auto scene = GET_NETWORK_SCENE;		assert(scene != nullptr);
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
					auto scene = GET_NETWORK_SCENE;	assert(scene != nullptr);
					scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::JoinRoomComplete, scene,
						recvData.mRoomId));
				}
				else
				{
					//���� �÷��̾� ó�� �ʿ�
				}
			}
			break;

		case PKT_SC_ALL_READY:
			{
				GameRunNotify recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);

				auto scene = GET_ROOM_SCENE;		assert(scene != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(RoomScene::GameStartComplete, scene));
			}
			return; // �� ���� ��Ŷ ���� ���� �ݹ��Լ� ȣ���� �ʿ��ϹǷ� ����

		case PKT_SC_CREATE_HERO:
			{
				CreateHeroResult recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);

				auto pos = Point(recvData.mPosX, recvData.mPosY);

				auto layer = GET_OBJECT_LAYER;		assert(layer != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::FirstDrawUnit, layer,
					recvData.mPlayerId, recvData.mUnitId, recvData.mUnitType, pos));
			}
			break;

		case PKT_SC_RUN_COMPLETE:
			{
				ServerRunCompleteNotify recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);

				auto layer = GET_LOADING_LAYER;		assert(layer != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(LoadingBGLayer::SetLoadingFin, layer));
			}
			return; // �� ���� ��Ŷ ���� ���� �ݹ��Լ� ȣ���� �ʿ��ϹǷ� ����

		case PKT_SC_START_GAME:
			{	
				StartGameNotify recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);

				auto scene = GET_M_GAME_SCENE;		assert(scene != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(MultiGameScene::StartGame, scene));
			}
			break;

		case PKT_SC_MOVE:
			{
				MoveBroadcastResult recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);
							
				auto curPos = Point(recvData.mCurrentPosX, recvData.mCurrentPosY);
				auto targetPos = Point(recvData.mTargetPosX, recvData.mTargetPosY);

				auto layer = GET_OBJECT_LAYER;		assert(layer != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitMove, layer,
					recvData.mUnitId, curPos, targetPos));
			}
			break;

		case PKT_SC_CRASH:
			{
				CrashedBroadcastResult recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);

				auto exPos = Point(recvData.mExpectPosX, recvData.mExpectPosY);
				auto revisionPos = Point(recvData.mCurrentPosX, recvData.mCurrentPosY);

				auto layer = GET_OBJECT_LAYER;		assert(layer != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitCrash, layer,
					recvData.mUnitId, exPos));

				if (!recvData.mIsCrashed)
				{
					scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitCrashEnd, layer,
						recvData.mUnitId, revisionPos));
				}
			}
			break;

		case PKT_SC_SKILL:
			{
				SkillBroadcastResult recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);

				auto curPos = Point(recvData.mCurrentPosX, recvData.mCurrentPosY);
				auto targetPos = Point(recvData.mTargetPosX, recvData.mTargetPosY);

				auto layer = GET_OBJECT_LAYER;		assert(layer != nullptr);
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::UnitSkillUse, layer,
					recvData.mUnitId, recvData.mKey, curPos, targetPos));
			}
			break;

		default:
			assert(false);
		}

	}
}


///////////////////////////////////////////////////////////////////////////
/*
	���� ��Ŷ �Ľ��ϴ� �Լ���
*/
///////////////////////////////////////////////////////////////////////////
void TcpClient::loginRequest()
{
	if (mLoginId > 0)
		return;

	srand(time(NULL));

	LoginRequest sendData;
	sendData.mPlayerId = 1000 + rand() % 101;	// ���̵� �ӽ÷� ���� ����

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

void TcpClient::startGameRequest()
{
	if (mLoginId < 0)
		return;

	GameReadyNotify sendData;
	sendData.mPlayerId = mLoginId;
	sendData.mHeroType = HERO_MAGICIAN;

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

void TcpClient::moveRequest(Point curPos, Point targetPos)
{
	if (mLoginId < 0)
		return;

	MoveRequest sendData;
	sendData.mPlayerId = mLoginId;
	sendData.mCurrentPosX = curPos.x;
	sendData.mCurrentPosY = curPos.y;
	sendData.mTargetPosX = targetPos.x;
	sendData.mTargetPosY = targetPos.y;

	send((const char*)&sendData, sizeof(MoveRequest));
}

void TcpClient::skillRequest(Point curPos, Point targetPos, SkillKey skillKey)
{
	if (mLoginId < 0)
		return;

	SkillRequest sendData;
	sendData.mPlayerId = mLoginId;
	sendData.mCurrentPosX = curPos.x;
	sendData.mCurrentPosY = curPos.y;
	sendData.mTargetPosX = targetPos.x;
	sendData.mTargetPosY = targetPos.y;
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
