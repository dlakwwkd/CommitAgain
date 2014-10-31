#pragma once
#include <string>
#include "CircularBuffer.h"

#ifndef _WIN32
#include <netdb.h>
#include <unistd.h>
#else
#include <winsock2.h>
#endif

#define BUF_SIZE	32768

class TcpClient
{
public:
	static TcpClient* getInstance();
	static void destroyInstance();

	SOCKET checkSocket(){ return mSock; }
	bool connect();
	void disconnect();

	void loginRequest();
	void makeRoomRequest();
	void joinRoomRequest();
	void outRoomRequest(int roomId);
	void createRequest(int unitID, float x, float y);

	void moveRequest(float x, float y);
	void chatRequest(const char* chat);

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

