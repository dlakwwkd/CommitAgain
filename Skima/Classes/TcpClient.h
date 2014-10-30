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

	SOCKET checkSocket(){ return m_sock; }
	bool connect();
	void disconnect();

	void loginRequest();
	void makeRoomRequest();
	void chatRequest(const char* chat);
	void moveRequest(float x, float y);
	void createRequest(int unitID, float x, float y);
	
private:
	TcpClient();
	virtual ~TcpClient();

	bool send(const char* data, int length);
	void networkThread();
	void processPacket();

private:
	SOCKET			m_sock;
	CircularBuffer	m_recvBuffer;
	int				m_loginId;
};

