#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"
#include "Game.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "Scheduler.h"
#include "Config.h"

GameManager* GGameManager = nullptr;


GameRoom* GameManager::CreateRoom()
{
	if (m_MakeRoomNum == 0)
		LowTick();

	GameRoom* room = new GameRoom(++m_MakeRoomNum);

	if (m_RoomList[m_MakeRoomNum] != nullptr)
		delete m_RoomList[m_MakeRoomNum];

	m_RoomList[m_MakeRoomNum] = room;

	return room;
}

GameRoom* GameManager::SearchRoom(int roomId)
{
	for (auto& room : m_RoomList)
	{
		if (room.first == roomId)
		{
			return room.second;
		}
	}
	printf(" - No Room ! \n");
	return nullptr;
}

int GameManager::SearchEmptyRoom()
{
	for (auto& room : m_RoomList)
	{
		if (room.second->IsJoinAble())
		{
			return room.second->GetRoomID();
		}
	}
	printf(" - No Room ! \n");
	return -1;
}

void GameManager::JoinRoom(int playerId, int roomId)
{
	m_RoomList[roomId]->JoinPlayer(playerId);
}

void GameManager::OutRoom(int playerId, int roomId)
{
	m_RoomList[roomId]->OutPlayer(playerId);

	if (m_RoomList[roomId]->GetPlayerListNum() == 0)
	{
		delete m_RoomList[roomId];

		for (RoomList::iterator iter = m_RoomList.begin(); iter != m_RoomList.end(); ++iter)
		{
			if (iter->first == roomId)
			{
				m_RoomList.erase(iter);
				break;
			}
		}
		printf(" - Destroy %d Room ! \n", roomId);
	}
}


void GameManager::CreateGame(int roomId)
{
	Game* game = new Game(roomId);

	if (m_GameList[roomId] != nullptr)
		delete m_GameList[roomId];

	m_GameList[roomId] = game;

	game->SetPlayerList(m_RoomList[roomId]->GetPlayerList());
}


///////////////////////////////////////////////////////////////////////////
/*
	물리세계 구축
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::InitPhyWorld()
{
	b2Vec2 gravity(0.0f, 0.0f);
	m_World = new b2World(gravity);

	m_World->SetAllowSleeping(true);
	m_World->SetContinuousPhysics(true);
}
void GameManager::DeletePhyWorld()
{
	delete m_World;
}

///////////////////////////////////////////////////////////////////////////
/*
	매 프레임마다 실행	
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::Tick(float dt)
{
	m_World->Step(dt, 8, 3);

	for (auto& game : m_GameList)
	{
		for (auto& player : game.second->GetPlayerList())
		{
			auto client = GClientManager->GetClient(player.first);
			auto unit = player.second->GetMyHero();
			client->SendUnitInfo(unit->GetUnitID(), unit->GetUnitType(), unit->GetCurrentPos());
		}
	}

}

///////////////////////////////////////////////////////////////////////////
/*
	MANAGER_UPDATE_INTERVAL 주기로 실행
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::LowTick()
{
	for (auto& it : m_RoomList)
	{
		;
	}

	CallFuncAfter(MANAGER_UPDATE_INTERVAL, this, &GameManager::LowTick);
}
