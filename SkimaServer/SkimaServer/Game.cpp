#include "stdafx.h"
#include "Game.h"
#include "GameRoom.h"
#include "Player.h"
#include "Map.h"
#include "Rock.h"
#include "ClientSession.h"


Game::Game(GameRoom* room)
{
    m_GameID = room->m_RoomID;
    m_IsReady = true;
    m_IsStart = false;
	m_IsEnd = false;
    m_LoadedPlayerNum = 0;

    for (auto& player : room->m_PlayerList)
    {
        m_PlayerList[player.first] = player.second;
    }

    m_MapObjectList.clear();
}

Game::~Game()
{
    delete m_Computer;
}

void Game::InitGame()
{
	m_IsEnd = false; 

    // 주의: 여기서부턴 하드코딩의 구간입니다.^^
    ClientSession* temp;
    int i = 0;
    for (auto& it : m_PlayerList)
    {
        b2Vec2 createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 2 };
        auto roomId = it.second->GetRoomID();
        if (++i == 2)
        {
            createPos.x += MAX_MAP_SIZE_X / 2;
            temp = it.second->GetClient();
        }
        it.second->CreateHero(CONVERT_IN(createPos, roomId));
    }

    m_Computer = new Player(temp, COMPUTER, COMPUTER);  // 100번 보면 이해됨.
    InitMap();
}

void Game::InitMap()
{
    auto player = m_PlayerList.begin()->second;
    
    //나중에 "for문"화 할 거임
    for (int i = 0; i < 5; ++i)
    {
        auto pos = b2Vec2(rand() % MAX_MAP_SIZE_X, rand() % MAX_MAP_SIZE_Y);
        auto roomId = player->GetRoomID();
        Rock* rock = new Rock(m_Computer, b2Vec2(CONVERT_IN(pos, roomId)));

        m_MapObjectList.push_back(rock);
        player->GetClient()->SendMapInfo(rock->GetUnitID(), rock->GetBody()->GetPosition());
    }
}

void Game::EndGame()
{
	m_IsEnd = true;

    for (auto& mapObject : m_MapObjectList)
    {
        delete mapObject;
        mapObject = nullptr;
    }
    m_MapObjectList.clear();

	for (auto& player : m_PlayerList)
	{
		player.second->UnitListClear();
	}
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

    player->second->UnitListClear();
    m_PlayerList.erase(player);

    printf("\n [Out  Game] Game ID %d, Player ID: %d \n", m_GameID, playerId);
}
