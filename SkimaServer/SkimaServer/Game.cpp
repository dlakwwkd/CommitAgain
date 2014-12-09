#include "stdafx.h"
#include "Game.h"
#include "GameRoom.h"
#include "Player.h"
#include "Map.h"
#include "Rock.h"


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

void Game::InitGame()
{
	m_IsEnd = false; 

    int i = 0;
    for (auto& it : m_PlayerList)
    {
        b2Vec2 createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 2 };
        auto roomId = it.second->GetRoomID();
        if (++i == 2)
        {
            createPos.x += MAX_MAP_SIZE_X / 2;
        }
        it.second->CreateHero(CONVERT_IN(createPos, roomId));
    }
}

void Game::InitMap()
{
    //나중에 "for문"화 할 거임

    b2Vec2 pos = { 100, 100 };
    auto rock = new Rock(pos);

    m_MapObjectList.push_back(rock);

    MapObt mapObtList[1];
    mapObtList[0].unitId = rock->GetUnitID();
    mapObtList[0].pos.x = EXTEND(pos.x);
    mapObtList[0].pos.x = EXTEND(pos.y);

}

void Game::EndGame()
{
	m_IsEnd = true;

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
