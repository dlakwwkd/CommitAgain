#include "stdafx.h"
#include "GameRoom.h"


void GameRoom::OutPlayer(int id)
{
	for (auto it = m_PlayerIdList.begin(); it != m_PlayerIdList.end(); ++it)
	{
		if (*it == id)
		{
			m_PlayerIdList.erase(it);
		}
	}
}
