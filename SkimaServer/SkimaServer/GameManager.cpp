#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"
#include "Game.h"
#include "Player.h"
#include "ClientManager.h"
#include "ClientSession.h"
#include "ContactListener.h"
#include "Scheduler.h"
#include "Config.h"

GameManager* GGameManager = nullptr;


///////////////////////////////////////////////////////////////////////////
/*
	GameRoom 관련
*/
///////////////////////////////////////////////////////////////////////////
GameRoom* GameManager::CreateRoom()
{
	if (m_MakeRoomNum == 0)
		LowTick();

	GameRoom* room = new GameRoom(++m_MakeRoomNum);

	if (m_RoomList[m_MakeRoomNum] != nullptr)
	{
		delete m_RoomList[m_MakeRoomNum];
	}
	m_RoomList[m_MakeRoomNum] = room;
	return room;
}

void GameManager::DeleteRoom(int roomId)
{
	for (auto& iter = m_RoomList.begin(); iter != m_RoomList.end(); ++iter)
	{
		if (iter->first == roomId)
		{
			delete iter->second;
			m_RoomList.erase(iter);
			break;
		}
	}
	printf(" - Destroy %d Room ! \n", roomId);
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
	printf(" - Room Search Failed ! \n");
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

void GameManager::JoinRoom(int id, Player* player, int roomId)
{
	m_RoomList[roomId]->JoinPlayer(id, player);
}

void GameManager::OutRoom(int playerId, int roomId)
{
	m_RoomList[roomId]->OutPlayer(playerId);

	if (m_RoomList[roomId]->GetPlayerList().size() == 0)
	{
		DeleteRoom(roomId);
	}
}



///////////////////////////////////////////////////////////////////////////
/*
	Game 관련
*/
///////////////////////////////////////////////////////////////////////////
Game* GameManager::SearchGame(int playerId)
{
	for (auto& game : m_GameList)
	{
		for (auto& player : game.second->GetPlayerList())
		{
			if (player.first == playerId)
			{
				return game.second;
			}
		}
	}
	printf(" - Game Search Failed ! \n");
	return nullptr;
}

void GameManager::CreateGame(int roomId)
{
	Game* game = new Game(roomId);

	if (m_GameList[roomId] != nullptr)
	{
		delete m_GameList[roomId];
	}
	m_GameList[roomId] = game;
	game->SetPlayerList(m_RoomList[roomId]->GetPlayerList());
}

void GameManager::DeleteGame(int gameId)
{
	for (auto& iter = m_GameList.begin(); iter != m_GameList.end(); ++iter)
	{
		if (iter->first == gameId)
		{
			delete iter->second;
			m_GameList.erase(iter);
			break;
		}
	}
	printf(" - Destroy %d Game ! \n", gameId);
}



///////////////////////////////////////////////////////////////////////////
/*
	Player 관련
*/
///////////////////////////////////////////////////////////////////////////
Player* GameManager::SearchPlayer(int playerId)
{
	return SearchGame(playerId)->GetPlayer(playerId);
}

void GameManager::PlayerOut(int playerId)
{
	for (auto& game : m_GameList)
	{
		for (auto& player : game.second->GetPlayerList())
		{
			if (player.first == playerId)
			{
				game.second->PlayerOut(playerId);
				break;
			}
		}
	}
}

// void GameManager::UnitMoveSet(b2Vec2 targetPos, b2Vec2 currentPos, int playerId)
// {
// 	for (auto& game : m_GameList)
// 	{
// 		for (auto& player : game.second->GetPlayerList())
// 		{
// 			if (player.first == playerId)
// 			{
// 				player.second->GetMyHero()->SetCurrentPos(currentPos);
// 				player.second->GetMyHero()->SetTargetPos(targetPos);
// 				player.second->GetMyHero()->SetAverageMove(targetPos);
// 				break;
// 			}
// 		}
// 	}
// }




///////////////////////////////////////////////////////////////////////////
/*
	매 프레임마다 실행	
*/
///////////////////////////////////////////////////////////////////////////
void GameManager::Tick(float dt)
{
	m_World->Step(dt, 8, 3);

	for (auto& room : m_RoomList)
	{
		if (room.second->IsAllReady())
		{
			// 게임 구동 시작!;
			printf(" - All Player is Ready ! :: %d Room is Game Start !! \n", room.first);
			CallFuncAfter(MANAGER_UPDATE_INTERVAL, this, &GameManager::CreateGame, room.first);
			room.second->InitReady();
		}
	}

	for (auto& game : m_GameList)
	{
		for (auto& player : game.second->GetPlayerList())
		{
			auto client = GClientManager->GetClient(player.first);	_ASSERT(client != nullptr);

			if (game.second->IsReady())
			{
				CallFuncAfter(MANAGER_UPDATE_INTERVAL, client, &ClientSession::ServerRunComplete);
				game.second->SetIsReady(false);
			}

			if (game.second->GetLoadedPlayerNum() >= 2 && !game.second->IsStart())
			{
				client->StartGame();
				game.second->SetIsStart(true);
			}

			if (!game.second->IsStart())
				continue;

			for (auto& unit : player.second->GetUnitList())
			{
				unit.second->Movement();
			}
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
	

	CallFuncAfter(MANAGER_UPDATE_INTERVAL, this, &GameManager::LowTick);
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

	m_Contact = new ContactListener();
	m_World->SetContactListener((b2ContactListener*)m_Contact);
}

void GameManager::DeletePhyWorld()
{
	delete m_World;
	delete m_Contact;
}


