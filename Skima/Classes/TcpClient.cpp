#include <thread>
#include "TcpClient.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "2d/CCLabel.h"
#include "GameScene.h"
#include "ObjectLayer.h"
#include "NetworkScene.h"
#include "../../PacketType.h"
#include "Enums.h"


#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#define sleep(x) Sleep(x)
#endif

static TcpClient* s_TcpClient = nullptr;

TcpClient::TcpClient() : m_recvBuffer(BUF_SIZE), m_sock(NULL), m_loginId(-1)
{

}

TcpClient::~TcpClient()
{
#ifndef _WIN32
	close(m_sock);
#else
	closesocket(m_sock);
	WSACleanup();
#endif

}

bool TcpClient::initialize()
{

#ifdef _WIN32
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;
#endif


	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)
		return false;

	/// thread start
	auto t = std::thread(CC_CALLBACK_0(TcpClient::networkThread, this));
	t.detach();

	return true;
}


TcpClient* TcpClient::getInstance()
{
	if (nullptr == s_TcpClient)
	{
		s_TcpClient = new TcpClient();
		if (false == s_TcpClient->initialize())
			return nullptr;

		std::string ipaddr = cocos2d::UserDefault::getInstance()->getStringForKey("ipaddr", std::string("localhost"));
		int port = cocos2d::UserDefault::getInstance()->getIntegerForKey("port", 9001);

		s_TcpClient->connect(ipaddr.c_str(), port);
	}
		

	return s_TcpClient;
}

void TcpClient::destroyInstance()
{
	CC_SAFE_DELETE(s_TcpClient);
}

bool TcpClient::connect(const char* serverAddr, int port)
{
	struct hostent* host;
	struct sockaddr_in hostAddr;

	if ((host = gethostbyname(serverAddr)) == 0) 
		return false;

	memset(&hostAddr, 0, sizeof(hostAddr));
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	hostAddr.sin_port = htons(port);

	if (SOCKET_ERROR == ::connect(m_sock, (struct sockaddr*)&hostAddr, sizeof(hostAddr)))
	{
		CCLOG("CONNECT FAILED");
		return false;
	}
	
	//u_long arg = 1;
	//ioctlsocket(mSocket, FIONBIO, &arg);

	/// nagle �˰����� ����
	int opt = 1;
	setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int));

	return true;
}

bool TcpClient::send(const char* data, int length)
{
	int count = 0;
	while (count < length) 
	{
		int n = ::send(m_sock, data + count, length, 0);
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

		int n = ::recv(m_sock, inBuf, 4096, 0);

		if (n < 1)
		{
			sleep(0); ///< for cpu low-utilization
			continue;
		}
			

		if (!m_recvBuffer.Write(inBuf, n))
		{
			/// ���� ��á��. 
			assert(false);
		}

		processPacket();
	}
}

void TcpClient::processPacket()
{
	auto scheduler = cocos2d::Director::getInstance()->getScheduler();

	/// ��Ŷ�� �Ľ��ؼ� �ϼ��Ǵ� ��Ŷ�� ������, �ش� �ݹ��� �ҷ��ش�. 
	while (true)
	{
		PacketHeader header;

		if (false == m_recvBuffer.Peek((char*)&header, sizeof(PacketHeader)))
			break;
			

		if (header.mSize > m_recvBuffer.GetStoredSize())
			break;
	

		switch (header.mType)
		{
		case PKT_SC_LOGIN:
			{
				LoginResult recvData;
				bool ret = m_recvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);
				//("LOGIN OK: ID[%d] Name[%s]", recvData.mPlayerId, recvData.mName);
	
				m_loginId = recvData.mPlayerId;

				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("Network Layer");
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(NetworkScene::connectComplit, dynamic_cast<NetworkScene*>(layer)));


// 				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("Game Layer")->getChildByName("Physhics Layer")->getChildByName("Object Layer");
// 				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::createHeroStart, dynamic_cast<ObjectLayer*>(layer)));


			}
			break;


		case PKT_SC_CREATE_HERO:
			{
				CreateHeroResult recvData;
				bool ret = m_recvBuffer.Read((char*)&recvData, recvData.mSize);
				assert(ret && recvData.mPlayerId != -1);


				auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("Game Layer")->getChildByName("Physhics Layer")->getChildByName("Object Layer");
				scheduler->performFunctionInCocosThread(CC_CALLBACK_0(ObjectLayer::updatePeer, dynamic_cast<ObjectLayer*>(layer), recvData.mUnitId, recvData.mPosX, recvData.mPosY));

			}
			break;

		default:
			assert(false);
		}

	}
}

void TcpClient::loginRequest()
{
	if (m_loginId > 0)
		return;

	srand(time(NULL));

	LoginRequest sendData;
	sendData.mPlayerId = 1000 + rand() % 101;

	send((const char*)&sendData, sizeof(LoginRequest));
}

void TcpClient::makeRoomRequest()
{
	if (m_loginId < 0)
		return;

	srand(time(NULL));

	LoginRequest sendData;
	sendData.mPlayerId = 1000 + rand() % 101;

	send((const char*)&sendData, sizeof(LoginRequest));
}

void TcpClient::chatRequest(const char* chat)
{
	if (m_loginId < 0)
		return;

	ChatBroadcastRequest sendData;

	sendData.mPlayerId = m_loginId;
	memcpy(sendData.mChat, chat, strlen(chat));

	send((const char*)&sendData, sizeof(ChatBroadcastRequest));
}


void TcpClient::moveRequest(float x, float y)
{
	if (m_loginId < 0)
		return;

	MoveRequest sendData;
	sendData.mPlayerId = m_loginId;
	sendData.mPosX = x;
	sendData.mPosY = y;

	send((const char*)&sendData, sizeof(MoveRequest));
}

void TcpClient::createRequest(int unitID, float x, float y)
{
	if (m_loginId < 0)
		return;

	CreateHeroRequest sendData;
	sendData.mPlayerId = m_loginId;
	sendData.mUnitId = unitID;
	sendData.mPosX = x;
	sendData.mPosY = y;

	send((const char*)&sendData, sizeof(CreateHeroRequest));

}