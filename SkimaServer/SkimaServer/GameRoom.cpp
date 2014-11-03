#include "stdafx.h"
#include "GameRoom.h"


void GameRoom::ReadySign()
{
	if (++m_ReadyNum >= 2)
	{
		m_IsAllReady = true;
	}
}

void GameRoom::JoinPlayer(int id)
{
	m_PlayerIdList.push_back(id);

	printf("\n [Join Room] Room ID %d, Player ID: %d \n", m_RoomID, id);

	if (m_PlayerIdList.size() >= 2)
	{
		printf(" - Room %d is Full ! \n", m_RoomID);
		m_JoinAble = false;
	}
}


void GameRoom::OutPlayer(int id)
{
	for (auto& it = m_PlayerIdList.begin(); it != m_PlayerIdList.end(); ++it)
	{
		if (*it == id)
		{
			m_PlayerIdList.erase(it);
			break;
		}
	}
	if (m_PlayerIdList.size() != 0)
		m_JoinAble = true;

	printf("\n [Out  Room] Room ID %d, Player ID: %d \n", m_RoomID, id);
}
