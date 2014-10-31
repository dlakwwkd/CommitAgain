#pragma once

#include <map>
#include <WinSock2.h>
#include "Config.h"
#include "..\..\PacketType.h"
#include "CircularBuffer.h"
#include "ObjectPool.h"
#include "RefCountable.h"


class ClientSession ;
class ClientManager ;
//struct DatabaseJobContext ;

struct OverlappedIO : public OVERLAPPED
{
	OverlappedIO() : mObject(nullptr)
	{}

	ClientSession* mObject ;
} ;

class ClientSession : public RefCountable, public ObjectPool<ClientSession>
{
public:
	ClientSession(SOCKET sock)
		: mConnected(false), mLogon(false), mSocket(sock), m_PlayerId(-1), mSendBuffer(BUFSIZE), mRecvBuffer(BUFSIZE)
	{
		memset(&mClientAddr, 0, sizeof(SOCKADDR_IN)) ;
		memset(m_PlayerName, 0, sizeof(m_PlayerName)) ;
	}
	virtual ~ClientSession() {}

public:
	int	GetPlayerId() const	{ return m_PlayerId; }
	const char* GetPlayerName() const { return m_PlayerName;  }
	SOCKET GetSocketKey() const { return mSocket;  }

	void	LoginSuccessInform(int id);


// 	void	LoginDone(int pid, const char* name);
// 	void	UpdateDone();

public: 
	bool	IsConnected() const { return mConnected; }
	void	OnTick();
//	void	OnDbUpdate(); ///< �ֱ������� �����ͺ��̽��� ������Ʈ

	template <class PKT_TYPE>
	bool ParsePacket(PKT_TYPE& pkt)
	{
		return mRecvBuffer.Read((char*)&pkt, pkt.mSize);
	}

	void	OnRead(size_t len) ;
	void	OnWriteComplete(size_t len) ;

	bool	OnConnect(SOCKADDR_IN* addr) ;
	
	bool	PostRecv() ;

	bool	SendRequest(PacketHeader* pkt) ;
	bool	Broadcast(PacketHeader* pkt) ;

	void	Disconnect() ;

	bool	SendFlush(); ///< Send��û ���ΰ͵� ��Ƽ� ����
//	void	DatabaseJobDone(DatabaseJobContext* result);

private:
	int				m_PlayerId;
	char			m_PlayerName[MAX_NAME_LEN];

private:
	bool			mConnected ;
	bool			mLogon ;
	SOCKET			mSocket ;
	SOCKADDR_IN		mClientAddr ;

	CircularBuffer	mSendBuffer ;
	CircularBuffer	mRecvBuffer ;

	OverlappedIO	mOverlappedSend ;
	OverlappedIO	mOverlappedRecv ;

	friend class ClientManager ;
} ;


void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
