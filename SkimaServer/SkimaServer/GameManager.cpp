#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"

GameManager* GGameManager = nullptr;


GameRoom* GameManager::CreateRoom()
{
	GameRoom* room = new GameRoom(++m_RoomNum);
	room->SetJoinAble();

	if (m_RoomList[m_RoomNum] != nullptr)
		delete m_RoomList[m_RoomNum];

	m_RoomList[m_RoomNum] = room;

	return room;
}

void GameManager::UpdateRoomState()
{
	for (auto& it : m_RoomList)
	{

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
	printf(" No Room!!!!!!!!! \n");
	return -1;
}

void GameManager::JoinRoom(int playerId, int roomId)
{
	m_RoomList[roomId]->JoinPlayer(playerId);
}

void GameManager::OutRoom(int playerId, int roomId)
{
	m_RoomList[roomId]->OutPlayer(playerId);
}
