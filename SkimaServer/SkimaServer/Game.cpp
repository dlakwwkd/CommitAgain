﻿#include "stdafx.h"
#include "Game.h"
#include "GameRoom.h"
#include "GameManager.h"
#include "Player.h"
#include "Map.h"
#include "Rock.h"
#include "MoveRock.h"
#include "ClientSession.h"


Game::Game(GameRoom* room)
{
    m_Computer = nullptr;
    m_Map = nullptr;
    m_GameID = room->m_RoomID;
	m_IsStart = false;
    m_LoadedPlayerNum = 0;

    for (auto& player : room->m_PlayerList)
    {
        m_PlayerList[player.first] = player.second;
    }
    m_MapObjectList.reserve(MAX_OBSTRUCT_SIZE);
}

Game::~Game()
{
    delete m_Computer;
    delete m_Map;
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

void Game::InitGame()
{
    // 주의: 여기서부턴 하드코딩의 구간입니다.^^
    ClientSession* temp;
    int i = 0;
    for (auto& player : m_PlayerList)
    {
        player.second->SetTeam(TEAM_A);
        b2Vec2 createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 2 };
        auto roomId = player.second->GetRoomID();
        if (++i == 2)
        {
            player.second->SetTeam(TEAM_B);
            createPos.x += MAX_MAP_SIZE_X / 2;
            temp = player.second->GetClient();
        }
        player.second->CreateHero(CONVERT_IN(createPos, roomId));
    }
    m_Computer = new Player(temp, COMPUTER, COMPUTER);  // 100번 보면 이해됨.
    InitMap();
    temp->ServerRunComplete();
}

void Game::InitMap()
{
    auto player = m_PlayerList.begin()->second;
    auto roomId = player->GetRoomID();
    m_Map = new Map(roomId);
    
    for (int i = 0; i < 5; ++i)
    {
        auto pos = b2Vec2(rand() % MAX_MAP_SIZE_X, rand() % MAX_MAP_SIZE_Y);
        MoveRock* rock = new MoveRock(m_Computer, b2Vec2(CONVERT_IN(pos, roomId)));

        m_MapObjectList.push_back(rock);
        player->GetClient()->SendMapInfo(rock->GetUnitID(), rock->GetBody()->GetPosition());
    }
}

void Game::EndGame()
{
	m_IsStart = false;

    for (auto& mapObject : m_MapObjectList)
    {
        delete mapObject;
        mapObject = nullptr;
    }
    m_MapObjectList.clear();

	for (auto& player : m_PlayerList)
	{
        player.second->SetTeam(NEUTRALITY);
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

    player->second->SetTeam(NEUTRALITY);
    player->second->UnitListClear();
    m_PlayerList.erase(player);

    printf("\n [Out  Game] Game ID %d, Player ID: %d \n", m_GameID, playerId);
}
