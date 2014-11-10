#pragma once
#include <string>
#include "CircularBuffer.h"

#ifndef _WIN32
#include <netdb.h>
#include <unistd.h>
#else
#include <winsock2.h>
#endif

#include "cocos2d.h"

USING_NS_CC;

#define BUF_SIZE	32768

class TcpClient
{
public:
	static TcpClient* getInstance();
	static void destroyInstance();

	SOCKET	checkSocket(){ return mSock; }
	int		getLoginId(){ return mLoginId; }
	bool connect();
	void disconnect();

	void loginRequest();
	void makeRoomRequest();
	void joinRoomRequest();
	void outRoomRequest(int roomId);
	void startGameRequest();
	void runCompleteRequest(); //이름 체인지 + bool값 인자

	void moveRequest(Point curPos, Point targetPos);


	//void chatRequest(const char* chat);

private:
	TcpClient();
	virtual ~TcpClient();

	bool send(const char* data, int length);
	void networkThread();
	void processPacket();

private:
	SOCKET			mSock;
	CircularBuffer	mRecvBuffer;
	int				mLoginId;
};

