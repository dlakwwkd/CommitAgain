#include "stdafx.h"
#include "Game.h"
#include "GameRoom.h"
#include "GameManager.h"
#include "Player.h"
#include "Map.h"
#include "Rock.h"
#include "MoveRock.h"
#include "ClientSession.h"
#include "Scheduler.h"


Game::Game(GameRoom* room)
{
	m_IsStart = false;
    m_GameID = room->m_RoomID;
    m_LoadedPlayerNum = 0;

    for (auto& player : room->m_PlayerList)
    {
        m_PlayerList[player.first] = player.second;
    }
}

Game::~Game()
{
}

void Game::Tick(float dt)
{
    for (auto& player : m_PlayerList)
    {
        for (auto& unit : player.second->GetUnitList())
        {
            unit.second->Movement();
        }
    }
}

void Game::WaveTimer()
{
    
}

void Game::InitGame()
{
    // 주의: 여기서부턴 하드코딩의 구간입니다.^^
    ClientSession* temp;
    int i = 0;

    int roomId;
    for (auto& player : m_PlayerList)
    {
        player.second->SetTeam(TEAM_A);
        b2Vec2 createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 2 };
        roomId = player.second->GetRoomID();
        if (++i == 2)
        {
            player.second->SetTeam(TEAM_B);
            createPos.x += MAX_MAP_SIZE_X / 2;
            temp = player.second->GetClient();
        }
        player.second->CreateHero(CONVERT_IN(createPos, roomId));
    }
    m_Computer = new Player(temp, PT_COMPUTER, "Computer", PT_COMPUTER);// 100번 보면 이해됨.
    m_Computer->SetRoomID(roomId);
	m_PlayerList[PT_COMPUTER] = m_Computer;
    m_Computer->SetTeam(TEAM_C);

    m_Map = new Map(roomId);
    m_Map->InitMap(roomId, m_Computer);
    IncRefCount();

    temp->ServerRunComplete();
}

void Game::StartGame()
{
    m_IsStart = true;
    CallFuncAfter(6000, this, &Game::LavaCreate, 6000);
}

void Game::EndGame()
{
	m_IsStart = false;

	auto computer = m_PlayerList.find(PT_COMPUTER);
	if (computer != m_PlayerList.end())
	{
        computer->second->UnitListClear();
		delete computer->second;
        computer->second = nullptr;
		m_PlayerList.erase(computer);
        m_Computer = nullptr;
	}
	delete m_Map;

	for (auto& player : m_PlayerList)
	{
        player.second->SetTeam(TEAM_N);
        player.second->UnitListClear();
	}
    DecRefCount();
}

Player* Game::GetPlayer(int playerId)
{
    if (playerId < 0)
    {
        printf(" - GetPlayer Failed ! : playerId is invalid \n");
        return nullptr;
    }
    auto player = m_PlayerList.find(playerId);
    if (player == m_PlayerList.end())
    {
        printf(" - GetPlayer Failed ! : relevant player isn't \n");
        return nullptr;
    }
    return player->second;
}

void Game::OutPlayer(int playerId)
{
    if (playerId < 0)
    {
        printf(" - OutPlayer Failed ! : playerId is invalid \n");
        return;
    }
    auto player = m_PlayerList.find(playerId);
    if (player == m_PlayerList.end())
    {
        printf(" - OutPlayer Failed ! : relevant player isn't \n");
        return;
    }

    player->second->SetTeam(TEAM_N);
    player->second->UnitListClear();
    m_PlayerList.erase(player);

    printf("\n [Out  Game] Game ID %d, Player ID: %d \n", m_GameID, playerId);
}

void Game::LavaCreate(int time)
{
    if (!m_IsStart || m_Computer == nullptr)
    {
        return;
    }

    m_Map->LavaCreate(m_GameID, m_Computer);


    int nextTime = time * 9 / 10;

    if (nextTime < 300)
    {
        nextTime = 300;
    }
    
    CallFuncAfter(nextTime, this, &Game::LavaCreate, nextTime);
    
}
