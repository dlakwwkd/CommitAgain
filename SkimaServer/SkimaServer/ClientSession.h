#pragma once

#include <map>
#include <WinSock2.h>
#include "Config.h"
#include "..\..\PacketType.h"
#include "CircularBuffer.h"
#include "ObjectPool.h"
#include "RefCountable.h"


class ClientSession;
class ClientManager;
//struct DatabaseJobContext ;

struct OverlappedIO : public OVERLAPPED
{
	OverlappedIO() : mObject(nullptr)
	{}
	ClientSession* mObject;
};

class ClientSession : public RefCountable, public ObjectPool<ClientSession>
{
public:
	ClientSession(SOCKET sock)
		: mConnected(false), mLogon(false), mSocket(sock), mPlayerId(-1), mRoomId(-1), mIsReady(false),
		mSendBuffer(BUFSIZE), mRecvBuffer(BUFSIZE)
	{
		memset(&mClientAddr, 0, sizeof(SOCKADDR_IN));
		memset(mPlayerName, 0, sizeof(mPlayerName));
	}
	virtual ~ClientSession() {}

public:
	int			GetPlayerId() const	{ return mPlayerId; }
	int			GetRoomId() const	{ return mRoomId; }
	const char* GetPlayerName() const { return mPlayerName; }
	SOCKET		GetSocketKey() const { return mSocket; }
	
	void		SetReady() { mIsReady = true; }
	bool		IsReady() { return mIsReady; }

	void		LoginSuccessInform(int id);
	void		MakeGameRoom(int id);
	void		JoinGameRoom();
	void		OutGameRoom();
	void		OutGame();
	void		AllReadyNotify();
	void		SendCreateHeroResult(int unitId, UnitType unitType, b2Vec2 pos);
	void		SendUnitInfo(int unitId, UnitType unitType, b2Vec2 pos);
	void		ServerRunComplete();
	void		StartGame();

	// 	void	LoginDone(int pid, const char* name);
	// 	void	UpdateDone();

public:
	bool	IsConnected() const { return mConnected; }
	void	OnTick();
	//	void	OnDbUpdate(); ///< 주기적으로 데이터베이스에 업데이트

	bool	OnConnect(SOCKADDR_IN* addr);
	bool	PostRecv();
	void	Disconnect();

	bool	SendRequest(PacketHeader* pkt);
	bool	SendFlush();
	bool	Broadcast(PacketHeader* pkt);
	//	void	DatabaseJobDone(DatabaseJobContext* result);

public:
	template <class PKT_TYPE>
	bool ParsePacket(PKT_TYPE& pkt){ return mRecvBuffer.Read((char*)&pkt, pkt.mSize); }

	void OnWriteComplete(size_t len);
	void OnRead(size_t len);

private:
	int				mRoomId;
	int				mPlayerId;
	char			mPlayerName[MAX_NAME_LEN];
	bool			mIsReady;

private:
	bool			mConnected;
	bool			mLogon;
	SOCKET			mSocket;
	SOCKADDR_IN		mClientAddr;

	CircularBuffer	mSendBuffer;
	CircularBuffer	mRecvBuffer;

	OverlappedIO	mOverlappedSend;
	OverlappedIO	mOverlappedRecv;

	friend class ClientManager;
};


void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
