#include <thread>
#include "TcpClient.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "2d/CCLabel.h"
#include "../../PacketType.h"
#include "GameScene.h"
#include "ObjectLayer.h"
#include "NetworkScene.h"
#include "RoomScene.h"


#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#define sleep(x) Sleep(x)
#endif

static TcpClient* s_TcpClient = nullptr;

TcpClient::TcpClient() : mRecvBuffer(BUF_SIZE), mSock(NULL), mLoginId(-1)
{
	/// 쓰레드 생성
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

	memset(&hostAddr, 0, sizeof(hostAddr));
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

				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("NetworkScene");
				if (layer == nullptr)
					break;
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::connectComplit, dynamic_cast<NetworkScene*>(layer)));
			}
			break;
		case PKT_SC_MAKE_ROOM:
			{
				MakeRoomResult recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId == mLoginId);

				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("RoomScene");
				if (layer == nullptr)
					break;
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(RoomScene::makeRoomComplit, dynamic_cast<RoomScene*>(layer), recvData.mRoomId));
			}
			break;


		case PKT_SC_CREATE_HERO:
			{
				CreateHeroResult recvData;
				bool ret = mRecvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);


				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->getChildByName("PhyshicsLayer")->getChildByName("ObjectLayer");
				// scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::createHeroStart, dynamic_cast<ObjectLayer*>(layer)));
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::updatePeer, dynamic_cast<ObjectLayer*>(layer), recvData.mUnitId, recvData.mPosX, recvData.mPosY));

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
	sendData.mPlayerId = 1000 + rand() % 101;

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

	MakeRoomRequest sendData;
	sendData.mPlayerId = mLoginId;

	send((const char*)&sendData, sizeof(MakeRoomRequest));
}





void TcpClient::createRequest(int unitID, float x, float y)
{
	if (mLoginId < 0)
		return;

	CreateHeroRequest sendData;
	sendData.mPlayerId = mLoginId;
	sendData.mUnitId = unitID;
	sendData.mPosX = x;
	sendData.mPosY = y;

	send((const char*)&sendData, sizeof(CreateHeroRequest));

}





void TcpClient::moveRequest(float x, float y)
{
	if (mLoginId < 0)
		return;

	MoveRequest sendData;
	sendData.mPlayerId = mLoginId;
	sendData.mPosX = x;
	sendData.mPosY = y;

	send((const char*)&sendData, sizeof(MoveRequest));
}



void TcpClient::chatRequest(const char* chat)
{
	if (mLoginId < 0)
		return;

	ChatBroadcastRequest sendData;

	sendData.mPlayerId = mLoginId;
	memcpy(sendData.mChat, chat, strlen(chat));

	send((const char*)&sendData, sizeof(ChatBroadcastRequest));
}

