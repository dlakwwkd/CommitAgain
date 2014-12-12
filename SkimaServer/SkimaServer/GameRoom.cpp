#include "stdafx.h"
#include "GameRoom.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Player.h"


void GameRoom::ReadySign()
{
    if (++m_ReadyNum >= MAX_PLAYER_NUM)
    {
        m_IsAllReady = true;
        printf(" - All Player is Ready ! :: %d Room is Game Start !! \n", m_RoomID);
        CallFuncAfter(1000, GGameManager, &GameManager::CreateGame, m_RoomID);
    }
    printf(" - Room[%d] ReadyNum: %d \n", m_RoomID, m_ReadyNum);
}

void GameRoom::InitReady()
{
    m_IsAllReady = false;
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
    m_PlayerList[player->GetPlayerID()] = player;
    player->SetRoomID(m_RoomID);
    printf("\n [Join Room] Room ID %d, Player ID: %d \n", m_RoomID, player->GetPlayerID());

    if (m_PlayerList.size() >= MAX_PLAYER_NUM)
    {
        m_JoinAble = false;
        printf(" - Room %d is Full ! \n", m_RoomID);
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

    m_PlayerList.erase(player);

    printf("\n [Out  Room] Room ID %d, Player ID: %d \n", m_RoomID, playerId);
    if (m_PlayerList.size() != 0)
    {
        m_JoinAble = true;
    }
}
