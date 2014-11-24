#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
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

	if (m_RoomList.find(m_MakeRoomNum) != m_RoomList.end())
	{
		DeleteRoom(m_MakeRoomNum);
	}
	GameRoom* room = new GameRoom(++m_MakeRoomNum);
	m_RoomList[m_MakeRoomNum] = room;
	return room;
}

void GameManager::DeleteRoom(int roomId)
{
	if (roomId < 0)
	{
		printf(" - DeleteRoom Failed ! : roomId is invalid \n");
		return;
	}
	auto room = m_RoomList.find(roomId);
	if (room == m_RoomList.end())
	{
		printf(" - DeleteRoom Failed ! : relevant room isn't \n");
		return;
	}
	delete room->second;
	m_RoomList.erase(room);
	printf(" - Destroy %d Room ! \n", roomId);
}

GameRoom* GameManager::SearchRoom(int roomId)
{
	if (roomId < 0)
	{
		printf(" - SearchRoom Failed ! : roomId is invalid \n");
		return nullptr;
	}
	auto room = m_RoomList.find(roomId);
	if (room == m_RoomList.end())
	{
		printf(" - SearchRoom Failed ! : relevant room isn't \n");
		return nullptr;
	}
	return room->second;
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

void GameManager::JoinRoom(int roomId, Player* player)
{
	if (roomId < 0 || player == nullptr)
	{
		printf(" - JoinRoom Failed ! : invalid info \n");
		return;
	}
	m_RoomList[roomId]->JoinPlayer(player);
}

void GameManager::OutRoom(int roomId, int playerId)
{
	if (roomId < 0 || playerId < 0)
	{
		printf(" - OutRoom Failed ! : invalid ID \n");
		return;
	}
	auto room = m_RoomList.find(roomId);
	if (room == m_RoomList.end())
	{
		printf(" - OutRoom Failed ! : relevant room isn't \n");
		return;
	}
	room->second->OutPlayer(playerId);

	if (room->second->GetPlayerList().size() == 0)
	{
		DeleteGame(roomId);
		DeleteRoom(roomId);
	}
}



///////////////////////////////////////////////////////////////////////////
/*
	Game 관련
*/
///////////////////////////////////////////////////////////////////////////
Game* GameManager::SearchGame(int gameId)
{
	if (gameId < 0)
	{
		printf(" - SearchGame Failed ! : gameId is invalid \n");
		return nullptr;
	}
	auto game = m_GameList.find(gameId);
	if (game == m_GameList.end())
	{
		printf(" - SearchGame Failed ! : relevant game isn't \n");
		return nullptr;
	}
	return game->second;
}

void GameManager::CreateGame(int gameId)
{
	if (gameId < 0)
	{
		printf(" - CreateGame Failed ! : gameId is invalid \n");
		return;
	}
	auto room = m_RoomList.find(gameId);
	if (room == m_RoomList.end())
	{
		printf(" - CreateGame Failed ! : room info is invalid \n");
		return;
	}
	if (m_GameList.find(gameId) != m_GameList.end())
	{
		DeleteGame(gameId);
	}
	Game* game = new Game(gameId);
	m_GameList[gameId] = game;
	game->SetPlayerList(&(room->second->GetPlayerList()));
	game->InitGame();
}

void GameManager::DeleteGame(int gameId)
{
	if (gameId < 0)
	{
		printf(" - DeleteGame Failed ! : gameId is invalid \n");
		return;
	}
	auto game = m_GameList.find(gameId);
	if (game == m_GameList.end())
	{
		printf(" - DeleteGame Failed ! : relevant game isn't \n");
		return;
	}
	delete game->second;
	m_GameList.erase(game);
	printf(" - Destroy %d Game ! \n", gameId);
}



///////////////////////////////////////////////////////////////////////////
/*
	Player 관련
*/
///////////////////////////////////////////////////////////////////////////
Player* GameManager::SearchPlayer(int playerId)
{
	if (playerId < 0)
	{
		printf(" - SearchPlayer Failed ! : playerId is invalid \n");
		return nullptr;
	}
	for (auto& room : m_RoomList)
	{
		for (auto& player : room.second->GetPlayerList())
		{
			if (player.first == playerId)
			{
				return player.second;
			}
		}
	}
	printf(" - SearchPlayer Failed ! : relevant player isn't \n");
	return nullptr;
}

void GameManager::PlayerOut(int playerId)
{
	if (playerId < 0)
	{
		printf(" - PlayerOut Failed ! : playerId is invalid \n");
		return;
	}
	auto player = SearchPlayer(playerId);
	if (player == nullptr)
	{
		printf(" - PlayerOut Failed ! : relevant player isn't \n");
		return;
	}
	OutRoom(player->GetRoomID(), playerId);
}




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
		for (auto& player : *(game.second->GetPlayerList()))
		{
			auto client = GClientManager->GetClient(player.first);
			if (client == nullptr)
			{
				auto room = m_RoomList.find(player.first);	_ASSERT(room != m_RoomList.end());
				room->second->OutPlayer(player.first);
				continue;
			}

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

bool GameManager::ApplyDamage(Unit* unitA, Unit* unitB)
{
	if (unitA->GetPlayerID() == unitB->GetPlayerID())
		return false;

	else
		return true;
}

void GameManager::ExchangeDamage(Unit* unitA, Unit* unitB)
{
	int damageA = unitA->GetUnitDamage();
	int damageB = unitB->GetUnitDamage();
	
	unitA->SetUnitHp(unitA->GetUnitHp() - damageB);
	unitB->SetUnitHp(unitB->GetUnitHp() - damageA);
}


