#include "stdafx.h"
#include "GameRoom.h"


void GameRoom::JoinPlayer(int id)
{
	m_PlayerIdList.push_back(id);

	if (m_PlayerIdList.size() >= 2)
	{
		printf(" Join Room ID: %d \n", m_RoomID);
		m_JoinAble = false;
	}
}


void GameRoom::OutPlayer(int id)
{
	for (auto it = m_PlayerIdList.begin(); it != m_PlayerIdList.end(); ++it)
	{
		if (*it == id)
			m_PlayerIdList.erase(it);
	}

	m_JoinAble = true;

	if (m_PlayerIdList.size() == 0)
	{
		printf(" Destroy Room ID: %d \n", m_RoomID);
		delete this;
	}
}
