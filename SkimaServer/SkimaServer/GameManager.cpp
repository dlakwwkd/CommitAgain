#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"

GameManager* GGameManager = nullptr;


GameRoom* GameManager::CreateRoom()
{
	GameRoom* room = new GameRoom(++m_MakeRoomNum);

	if (m_RoomList[m_MakeRoomNum] != nullptr)
		delete m_RoomList[m_MakeRoomNum];

	m_RoomList[m_MakeRoomNum] = room;

	return room;
}

void GameManager::UpdateRoomState()
{
	for (auto& it : m_RoomList)
	{
		;
	}
}

int GameManager::SearchRoom()
{
	for (auto& room : m_RoomList)
	{
		if (room.second->CheckJoinAble())
		{
			return room.second->GetRoomID();
		}
	}
	printf(" - No Room ! \n");
	return -1;
}

void GameManager::JoinRoom(int playerId, int roomId)
{
	m_RoomList[roomId]->JoinPlayer(playerId);
}

void GameManager::OutRoom(int playerId, int roomId)
{
	m_RoomList[roomId]->OutPlayer(playerId);

	if (m_RoomList[roomId]->GetPlayerListNum() == 0)
	{
		delete m_RoomList[roomId];

		for (RoomList::iterator iter = m_RoomList.begin(); iter != m_RoomList.end(); ++iter)
		{
			if (iter->first == roomId)
			{
				m_RoomList.erase(iter);
				break;
			}
		}
		printf(" - Destroy %d Room ! \n", roomId);
	}
}
