#include "stdafx.h"
#include "GameManager.h"
#include "GameRoom.h"

GameManager* GGameManager = nullptr;


GameRoom* GameManager::CreateRoom()
{
	GameRoom* room = new GameRoom(++m_RoomNum);

	if (m_RoomList[m_RoomNum] != nullptr)
		delete m_RoomList[m_RoomNum];

	m_RoomList[m_RoomNum] = room;

	return room;
}

void GameManager::UpdateRoomState()
{

}
