#include "pch.h"
#include "GameManager.h"
#include "Player.h"

GameManager::GameManager()
{
	m_IM = std::make_shared<InputManager>();
}

Player* GameManager::GetPlayer(int id)
{
	auto player = m_PlayerList.find(id);
	if (player != m_PlayerList.end())
	{
		return player->second;
	}
	return nullptr;
}

void GameManager::SetPlayer(int id)
{
	auto player = new Player();
	player->SetPlayerId(id);
	m_PlayerList.insert(std::make_pair(id, player));
}

void GameManager::DeletePlayer(int id)
{
	auto player = m_PlayerList.find(id);
	if (player != m_PlayerList.end())
	{
		delete player->second;
		m_PlayerList.erase(player);
	}
}

void GameManager::DeletePlayerAll()
{
	for (auto& player : m_PlayerList)
		delete player.second;
	m_PlayerList.clear();
}
