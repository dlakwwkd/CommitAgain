#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"


void Game::InitGame()
{
	int i = 1;

	for (auto& it : *m_PlayerList)
	{
        if (i == 1)
            it.second->CreateHero({ REDUCE(MAX_MAP_SIZE_X / 4), REDUCE(MAX_MAP_SIZE_Y / 2) });
		else
            it.second->CreateHero({ REDUCE(MAX_MAP_SIZE_X - MAX_MAP_SIZE_X / 4), REDUCE(MAX_MAP_SIZE_Y / 2) });

		i++;
	}
}

Player* Game::GetPlayer(int playerId)
{
	if (playerId < 0)
	{
		printf(" - GetPlayer Failed ! : playerId is invalid \n");
		return nullptr;
	}
	auto player = m_PlayerList->find(playerId);
	if (player == m_PlayerList->end())
	{
		printf(" - GetPlayer Failed ! : relevant player isn't \n");
		return nullptr;
	}
	return player->second;
}
