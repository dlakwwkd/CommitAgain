#include "stdafx.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "..\..\PacketType.h"
#include "Main.h"
#include "ThreadLocal.h"
#include "Player.h"
//#include "DatabaseJobContext.h"
//#include "DatabaseJobManager.h"

ClientManager* GClientManager = nullptr;


///////////////////////////////////////////////////////////////////////////
/*
	aceept된 패킷을 관리하는(즉, 연결된 클라와 1:1로 대응되는)
	ClientSession 생성
	*/
///////////////////////////////////////////////////////////////////////////
ClientSession* ClientManager::CreateClient(SOCKET sock)
{
	assert(LThreadType == THREAD_CLIENT);

	ClientSession* client = new ClientSession(sock);
	mClientList.insert(ClientList::value_type(sock, client));

	return client;
}

ClientSession* ClientManager::GetClient(int playerId)
{
	if (playerId < 0)
	{
		printf(" - GetClient Failed ! : playerId is invalid \n");
		return nullptr;
	}
	for (auto& client : mClientList)
	{
		auto player = client.second->GetPlayer();
		if (player == nullptr)
		{
			continue;
		}
		if (player->GetPlayerID() == playerId)
		{
			return client.second;
		}
	}
	return nullptr;
}

bool ClientManager::IsValidPlayerId(int playerId)
{
	if (playerId < 0)
	{
		printf(" - IsValidPlayerId Failed ! : playerId is invalid \n");
		return false;
	}
	for (auto& client : mClientList)
	{
		auto player = client.second->GetPlayer();
		if (player == nullptr)
		{
			continue;
		}
		if (player->GetPlayerID() == playerId)
		{
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
/*
	연결된 모든 클라의 출력버퍼에 동일한 패킷을 적재하는 함수
	(방송을 요청한 클라는 이미 보내기 처리한 상태이므로 제외)
	*/
///////////////////////////////////////////////////////////////////////////
void ClientManager::BroadcastPacket(ClientSession* from, PacketHeader* pkt)
{
	///FYI: C++ STL iterator 스타일의 루프
	for (ClientList::const_iterator it = mClientList.begin(); it != mClientList.end(); ++it)
	{
		ClientSession* client = it->second;

		if (from == client)
			continue;

		if (client == nullptr || client->GetPlayer() == nullptr)
		{
			printf(" - BroadcastPacket Failed ! : client is invalid \n");
			continue;
		}

		// 같은 방에 있는 애들에게만 방송한다.
		if (client->GetPlayer()->GetRoomID() == from->GetPlayer()->GetRoomID())
		{
			client->SendRequest(pkt);
		}
	}
}



///////////////////////////////////////////////////////////////////////////
/*
	서버의 매 프레임마다 실행되는 함수
	*/
///////////////////////////////////////////////////////////////////////////
void ClientManager::OnPeriodWork()
{
	/// 접속이 끊긴 세션들 주기적으로 정리 (1초 정도 마다 해주자)
	DWORD currTick = GetTickCount();
	if (currTick - mLastGCTick >= 1000)
	{
		CollectGarbageSessions();
		mLastGCTick = currTick;
	}

	/// 처리 완료된 DB 작업들 각각의 Client로 dispatch
	//DispatchDatabaseJobResults() ;
}



///////////////////////////////////////////////////////////////////////////
/*
	연결이 끊긴 클라이언트 세션 제거 처리
	*/
///////////////////////////////////////////////////////////////////////////
void ClientManager::CollectGarbageSessions()
{
	std::vector<ClientSession*> disconnectedSessions;

	///FYI: C++ 11 람다를 이용한 스타일
	std::for_each(mClientList.begin(), mClientList.end(),
		[&](ClientList::const_reference it)
	{
		ClientSession* client = it.second;

		if (false == client->IsConnected() && 0 == client->GetRefCount())
			disconnectedSessions.push_back(client);
	}
	);

	///FYI: C언어 스타일의 루프
	for (size_t i = 0; i < disconnectedSessions.size(); ++i)
	{
		ClientSession* client = disconnectedSessions[i];
		mClientList.erase(client->mSocket);
		delete client;
	}

}



///////////////////////////////////////////////////////////////////////////
/*
	연결된 모든 클라의 출력버퍼에 쌓인 패킷들 전부 전송하는 함수
	*/
///////////////////////////////////////////////////////////////////////////
void ClientManager::FlushClientSend()
{
	for (auto& it : mClientList)
	{
		ClientSession* client = it.second;
		if (false == client->SendFlush())
		{
			client->Disconnect();
		}
	}
}




/*
	DB 작업
	*/
// void ClientManager::DispatchDatabaseJobResults()
// {
// 	/// 쌓여 있는 DB 작업 처리 결과들을 각각의 클라에게 넘긴다
// 	DatabaseJobContext* dbResult = nullptr ;
// 	while ( GDatabaseJobManager->PopDatabaseJobResult(dbResult) )
// 	{
// 		if ( false == dbResult->mSuccess )
// 		{
// 			printf("DB JOB FAIL \n") ;
// 		}
// 		else
// 		{
// 			if ( typeid(*dbResult) == typeid(CreatePlayerDataContext) )
// 			{
// 				CreatePlayerDone(dbResult) ;
// 			}
// 			else if ( typeid(*dbResult) == typeid(DeletePlayerDataContext) )
// 			{
// 				DeletePlayerDone(dbResult) ;
// 			}
// 			else
// 			{
// 				/// 여기는 해당 DB요청을 했던 클라이언트에서 직접 해줘야 는 경우다
// 				auto& it = mClientList.find(dbResult->mSockKey) ;
// 
// 				if ( it != mClientList.end() && it->second->IsConnected() )
// 				{
// 					/// dispatch here....
// 					it->second->DatabaseJobDone(dbResult) ;
// 				}
// 			}
// 		}
// 	
// 	
// 		/// 완료된 DB 작업 컨텍스트는 삭제해주자
// 		DatabaseJobContext* toBeDelete = dbResult ;
// 		delete toBeDelete ;
// 	}
// }
// 
// void ClientManager::CreatePlayer(int pid, const char* name, const char* comment)
// {
// 	CreatePlayerDataContext* newPlayerJob = new CreatePlayerDataContext() ;
// 	newPlayerJob->mPlayerId = pid ;
// 	strcpy_s(newPlayerJob->mPlayerName, name) ;
// 	strcpy_s(newPlayerJob->mComment, comment) ;
// 
// 	GDatabaseJobManager->PushDatabaseJobRequest(newPlayerJob) ;
// 
// }
// 
// void ClientManager::DeletePlayer(int pid)
// {
// 	DeletePlayerDataContext* delPlayerJob = new DeletePlayerDataContext(pid) ;
// 	GDatabaseJobManager->PushDatabaseJobRequest(delPlayerJob) ;
// }
// 
// void ClientManager::CreatePlayerDone(DatabaseJobContext* dbJob)
// {
// 	CreatePlayerDataContext* createJob = dynamic_cast<CreatePlayerDataContext*>(dbJob) ;
// 
// 	printf("PLAYER[%d] CREATED: %s \n", createJob->mPlayerId, createJob->mPlayerName) ;
// }
// 
// void ClientManager::DeletePlayerDone(DatabaseJobContext* dbJob)
// {
// 	DeletePlayerDataContext* deleteJob = dynamic_cast<DeletePlayerDataContext*>(dbJob) ;
// 	
// 	printf("PLAYER [%d] DELETED\n", deleteJob->mPlayerId) ;
// 
// }