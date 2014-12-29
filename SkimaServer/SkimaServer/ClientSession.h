#pragma once
#include <WinSock2.h>
#include "Config.h"
#include "..\..\PacketType.h"
#include "CircularBuffer.h"
#include "ObjectPool.h"
#include "RefCountable.h"
class ClientSession;
class ClientManager;
class Player;
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
        : mConnected(false), mLogon(false), mSocket(sock), mSendBuffer(BUFSIZE), mRecvBuffer(BUFSIZE)
    {
        ZeroMemory(&mClientAddr, sizeof(SOCKADDR_IN));
    }
    virtual ~ClientSession() {}

public:
    SOCKET	GetSocketKey() const { return mSocket; }
    Player*	GetPlayer() const { return mPlayer; }

    void    LoginProcess(int playerId, const std::string& playerName);
    void    UpdateRoomInfo();
    void    MakeGameRoom(RoomInfo roomInfo);
    void    JoinGameRoom(RoomInfo roomInfo);
    void    OutGameRoom(RoomInfo roomInfo);

    void    PlayerReadyNotify();
    void    AllReadyNotify();
    void    ServerRunComplete();
    void	SendCreateHeroResult(			    int unitId, const b2Vec2& pos);
    void	SendMapInfo(        int playerId,   int unitId, const b2Vec2& pos);
    void    CreateMobBroadCast( int playerId,   int unitId, const b2Vec2& pos);
    void    ItemBroadCast(int playerId,   int unitId, const b2Vec2& pos,    bool isCreate);
    void    SendStartGame();

    void	TryMoveBroadCast(				    int unitId, const b2Vec2& curPos, const b2Vec2& targetPos);
    void	CrashedBroadCast(   int playerId,   int unitId, const b2Vec2& curPos, const b2Vec2& expectPos, bool isCrashed);
    void	SkillBroadCast(					    int unitId, const b2Vec2& curPos, const b2Vec2& targetPos, SkillKey key);
    void    UnHideBroadCast(                    int unitId, const b2Vec2& curPos);
    void    MeteorBroadCast(                    int unitId, const b2Vec2& targetPos);
    void	SplashSkillBroadCast(			    int unitId, const b2Vec2& curPos, const b2Vec2& targetPos, SkillKey key);
    void	ShootBroadCast(	    int playerId,	int unitId, const b2Vec2& curPos, const b2Vec2& targetPos);
    void	BlinkBroadCast(	    int playerId,	int unitId, const b2Vec2& curPos, const b2Vec2& targetPos);
    void    HpBroadCast(	    int playerId,	int unitId, int hp);
    void    BuffBroadCast(                      int unitId, float bonus, BuffTarget type);
    void    GameOverCast(	    int playerId);

    // 	void    LoginDone(int pid, const char* name);
    // 	void    UpdateDone();

public:
    bool    IsConnected() const { return mConnected; }
    void    OnTick();
    //	void    OnDbUpdate(); ///< 주기적으로 데이터베이스에 업데이트

    bool    OnConnect(SOCKADDR_IN* addr);
    bool    PostRecv();
    void    Disconnect();
    void    CloseSocketNoWait();

    bool    SendRequest(PacketHeader* pkt);
    bool    SendFlush();
    bool    Broadcast(PacketHeader* pkt);
    //	void    DatabaseJobDone(DatabaseJobContext* result);

public:
    template <class PKT_TYPE>
    bool ParsePacket(PKT_TYPE& pkt){ return mRecvBuffer.Read((char*)&pkt, pkt.mSize); }

    void OnWriteComplete(size_t len);
    void OnRead(size_t len);

private:
    Player*			mPlayer = nullptr;
    int             mRoomId = NULL;

private:
    bool            mConnected;
    bool            mLogon;
    SOCKET          mSocket;
    SOCKADDR_IN     mClientAddr;

    CircularBuffer  mSendBuffer;
    CircularBuffer  mRecvBuffer;

    OverlappedIO    mOverlappedSend;
    OverlappedIO    mOverlappedRecv;

    friend class ClientManager;
};


void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
