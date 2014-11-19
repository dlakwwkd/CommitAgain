#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"

void Game::SetPlayerList(PlayerList playerlist)
{
	m_PlayerList = playerlist;

	int i = 1;

	for (auto& it : playerlist)
	{
		if (i == 1)
			it.second->CreateHero({ 100 / PTM_RATIO, 100 / PTM_RATIO });
		else
			it.second->CreateHero({ (MAX_MAP_SIZE_X - 100) / PTM_RATIO, (MAX_MAP_SIZE_Y - 100) / PTM_RATIO });

		i++;
	}
}

void Game::InitGame()
{

}

void Game::PlayerOut(int playerId)
{
	if (playerId < 0) return;
	for (auto& iter = m_PlayerList.begin(); iter != m_PlayerList.end(); ++iter)
	{
		if (iter->first == playerId)
		{
			delete iter->second;
			m_PlayerList.erase(iter);
			break;
		}
	}
}

Player* Game::GetPlayer(int playerId)
{
	for (auto& player : m_PlayerList)
	{
		if (player.first == playerId)
		{
			return player.second;
		}
	}
	return nullptr;
}
