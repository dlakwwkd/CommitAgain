#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"

void Game::SetPlayerList(const std::vector<int>& playerIdList)
{
	int i = 0;
	for (auto& playerId : playerIdList)
	{
		m_PlayerList[playerId] = new Player(playerId);

		if (i == 0)
			m_PlayerList[playerId]->CreateHero({ 100, 100 });
		else
			m_PlayerList[playerId]->CreateHero({ MAX_MAP_SIZE_X - 100, MAX_MAP_SIZE_Y - 100 });

		i++;
	}
}

void Game::InitGame()
{


}

void Game::PlayerOut(int playerId)
{
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
