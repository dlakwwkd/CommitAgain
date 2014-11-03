#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"

Game::Game(int id)
{
}

void Game::InitGame()
{


}

void Game::SetPlayerList(std::vector<int>& playerList)
{
	int i = 0;
	for (auto& playerId : playerList)
	{
		m_PlayerList[playerId] = new Player(playerId);

		if (i == 0)
			m_PlayerList[playerId]->CreateHero({ 10, 10 });
		else
			m_PlayerList[playerId]->CreateHero({ MAX_MAP_SIZE_X - 10, MAX_MAP_SIZE_Y - 10 });

		i++;
	}
}
