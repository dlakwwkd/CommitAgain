﻿#pragma once
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

    void    LoginProcess(const std::string& playerName);
    void    UpdateRoomInfo();
    void    MakeGameRoom(const RoomInfo& roomInfo);
    void    JoinGameRoom(const RoomInfo& roomInfo);
    void    OutGameRoom(const RoomInfo& roomInfo);

    void    PlayerReadyNotify();
    void    AllPlayerReadyNotify();
    void    ServerRunComplete();
    void    SendCreateHeroResult(               int unitId, const b2Vec2& pos, RoomType roomType);
    void	SendMapInfo(        int playerId,   int unitId, const b2Vec2& pos);
    void    SendStartGame();

    void    TryMoveBroadCast(				    int unitId, const b2Vec2& targetPos);
    void    CrashedBroadCast(                   int unitId, const b2Vec2& curPos, const b2Vec2& expectPos);
    void    SyncPosBroadCast(                   int unitId, const b2Vec2& curPos);

    void	SkillBroadCast(					    int unitId, const b2Vec2& curPos, const b2Vec2& targetPos, SkillKey key);
    
    void	ShootBroadCast(	    int playerId,	int unitId, const b2Vec2& curPos, const b2Vec2& targetPos);
    
    void    CreateMobBroadCast( int playerId,   int unitId, const b2Vec2& pos, int hp, float speed);
    void    ItemBroadCast(      int playerId,   int unitId, const b2Vec2& pos, bool isCreate, BuffTarget buffType);
    
    void    BuffBroadCast(                      int unitId, float bonus, BuffTarget type, bool isOn);
    void    HideBroadCast(                      int unitId, bool isOn);
    void    EffectBroadCast(                                            EffectType type, const b2Vec2& pos);
    void    HpBroadCast(	    int playerId,   int unitId, int hp);
    
    void    GameOverCast(Team winTeam);

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
    template <class PKT_TYPE>
    bool ParsePacketWithCheckID(PKT_TYPE& pkt)
    {
        if (false == ParsePacket(pkt))
        {
            printf("[DEBUG] packet parsing error: %d \n", pkt.mType);
            return false;
        }
        if (mPlayer->GetPlayerID() != pkt.mPlayerId)
        {
            printf("[DEBUG] Player Info error! \n");
            return false;
        }
        return true;
    }

    void OnWriteComplete(size_t len);
    void OnRead(size_t len);

private:
    Player*			mPlayer = nullptr;

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
