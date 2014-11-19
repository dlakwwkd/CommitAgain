#include "stdafx.h"
#include "GameRoom.h"
#include "Player.h"


void GameRoom::ReadySign()
{
	if (++m_ReadyNum >= 2)
	{
		m_IsAllReady = true;
	}
}

void GameRoom::JoinPlayer(int id, Player* player)
{
	m_PlayerList[id] = player;

	printf("\n [Join Room] Room ID %d, Player ID: %d \n", m_RoomID, id);

	if (m_PlayerList.size() >= 2)
	{
		m_JoinAble = false;
		printf(" - Room %d is Full ! \n", m_RoomID);
	}
}

void GameRoom::OutPlayer(int id)
{
	for (auto& it = m_PlayerList.begin(); it != m_PlayerList.end(); ++it)
	{
		if (it->first == id)
		{
			delete it->second;
			m_PlayerList.erase(it);
			break;
		}
	}
	if (m_PlayerList.size() != 0)
		m_JoinAble = true;

	printf("\n [Out  Room] Room ID %d, Player ID: %d \n", m_RoomID, id);
}
