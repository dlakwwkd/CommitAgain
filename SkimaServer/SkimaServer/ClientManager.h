#pragma once
#include <WinSock2.h>
class ClientSession;
struct PacketHeader;
//struct DatabaseJobContext ;

typedef std::map<SOCKET, ClientSession*> ClientList;

class ClientManager
{
public:
    ClientManager() : mLastGCTick(0)
    {}

    ClientSession*  CreateClient(SOCKET sock);
    void            BroadcastPacket(ClientSession* from, PacketHeader* pkt);

    void            OnPeriodWork(DWORD currTick);
    void            FlushClientSend();

    bool            IsValidPlayerId(int playerId);

    /// DB에 플레이어 정보를 생성하거나 삭제하는 함수
    // 	void CreatePlayer(int pid, const char* name, const char* comment) ;
    // 	void DeletePlayer(int pid) ;
private:
    // 	void CreatePlayerDone(DatabaseJobContext* dbJob) ;
    // 	void DeletePlayerDone(DatabaseJobContext* dbJob) ;

private:
    void            CollectGarbageSessions();
    //void DispatchDatabaseJobResults() ;


private:
    ClientList      mClientList;
    DWORD           mLastGCTick;
};

extern ClientManager* GClientManager;