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
        : mConnected(false), mLogon(false), mSocket(sock), mSendBuffer(BUFSIZE), mRecvBuffer(BUFSIZE), mPlayer(nullptr)
    {
        ZeroMemory(&mClientAddr, sizeof(SOCKADDR_IN));
    }
    virtual ~ClientSession() {}

public:
    SOCKET	GetSocketKey() const { return mSocket; }
    Player*	GetPlayer() const { return mPlayer; }

    void    LoginProcess(int playerId);
    void    MakeGameRoom();
    void    JoinGameRoom();
    void    OutGameRoom();
    void    AllReadyNotify();
    void    SendCreateHeroResult(int unitId, b2Vec2 pos);
    void    SendMapInfo(int& mapObtList);
    void    SendHeroInfo(int unitId, b2Vec2 currentPos, b2Vec2 targetPos);
    void    CrashedBroadCast(int unitId, b2Vec2 curPos, b2Vec2 expectPos, bool isCrashed);
    void    SkillBroadCast(int heroId, SkillType type, SkillKey key, b2Vec2 currentPos, b2Vec2 targetPos);
	void    SplashSkillBroadCast(int heroId, SkillKey key, b2Vec2 currentPos, b2Vec2 targetPos);
    void    MissileBroadCast(int playerId, int unitId, b2Vec2 currentPos, b2Vec2 targetPos);
    void    TeleportBroadCast(int playerId, int unitId, b2Vec2 currentPos, b2Vec2 targetPos);
    void    HpBroadCast(int playerId, int unitId, int hp);
    void    ServerRunComplete();
    void    StartGame();
    void    GameOverCast(int playerId);

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
    Player*			mPlayer;

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
