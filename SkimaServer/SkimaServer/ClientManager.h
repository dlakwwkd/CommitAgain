#pragma once

#include <map>
#include <WinSock2.h>

class ClientSession;
struct PacketHeader;
//struct DatabaseJobContext ;

class ClientManager
{
public:
	ClientManager() : mLastGCTick(0)
	{}

	ClientSession* CreateClient(SOCKET sock);
	ClientSession* GetClient(int playerId);

	void BroadcastPacket(ClientSession* from, PacketHeader* pkt);

	void OnPeriodWork();
	void FlushClientSend();

	bool IsValidPlayerId(int playerId);

	/// DB�� �÷��̾� ������ �����ϰų� �����ϴ� �Լ�
	// 	void CreatePlayer(int pid, const char* name, const char* comment) ;
	// 	void DeletePlayer(int pid) ;
private:
	// 	void CreatePlayerDone(DatabaseJobContext* dbJob) ;
	// 	void DeletePlayerDone(DatabaseJobContext* dbJob) ;

private:
	void CollectGarbageSessions();
	//void DispatchDatabaseJobResults() ;


private:
	typedef std::map<SOCKET, ClientSession*> ClientList;
	ClientList	mClientList;
	DWORD		mLastGCTick;
};

extern ClientManager* GClientManager;