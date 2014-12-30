#include "stdafx.h"
#include "GameRoom.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Player.h"


void GameRoom::ReadySign()
{
    if (++m_ReadyNum >= m_PlayerList.size())
    {
        m_RoomInfo.mIsStart = true;
        printf(" - All Player is Ready ! :: %d Room is Game Start !! \n", m_RoomInfo.mRoomNum);
        CallFuncAfter(5000, GGameManager, &GameManager::CreateGame, m_RoomInfo.mRoomNum);
    }
    printf(" - Room[%d] ReadyNum: %d \n", m_RoomInfo.mRoomNum, m_ReadyNum);
}

void GameRoom::InitReady()
{
    m_ReadyNum = 0;

    for (auto &player : m_PlayerList)
    {
        player.second->SetReady(false);
    }
}


void GameRoom::JoinPlayer(Player* player)
{
    if (player == nullptr)
    {
        printf(" - JoinPlayer Failed ! : player is invalid \n");
        return;
    }
	auto iter = m_PlayerList.find(player->GetPlayerID());
	if (iter != m_PlayerList.end())
	{
		printf(" - JoinPlayer Failed ! : player is duplicated \n");
		return;
	}
    m_PlayerList[player->GetPlayerID()] = player;
    player->SetRoomID(m_RoomInfo.mRoomNum);
    m_RoomInfo.mCurPlayerNum++;
    printf("\n [Join Room] Room ID %d, Player ID: %d \n", m_RoomInfo.mRoomNum, player->GetPlayerID());

    if (m_PlayerList.size() >= m_RoomInfo.mMaxPlayerNum)
    {
        m_JoinAble = false;
        printf(" - Room %d is Full ! \n", m_RoomInfo.mRoomNum);
    }
}

void GameRoom::OutPlayer(int playerId)
{
    if (playerId < 0)
    {
        printf(" - OutPlayer Failed ! : playerId is invalid \n");
        return;
    }
    auto player = m_PlayerList.find(playerId);
    if (player == m_PlayerList.end())
    {
        printf(" - OutPlayer Failed ! : relevant player isn't \n");
        return;
    }
    if (player->second->IsReady())
    {
        --m_ReadyNum;
    }
    player->second->SetRoomID(-1);
    player->second->SetReady(false);
    m_RoomInfo.mCurPlayerNum--;

    m_PlayerList.erase(player);

    printf("\n [Out  Room] Room ID %d, Player ID: %d \n", m_RoomInfo.mRoomNum, playerId);
    if (m_PlayerList.size() != 0)
    {
        m_JoinAble = true;
    }
}
