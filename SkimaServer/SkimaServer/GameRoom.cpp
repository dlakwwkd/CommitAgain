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
    m_PlayerList[player->GetPlayerID()] = player; ///< 기존에 같의 아이디의 플레이어가 있는지 검사할 것. 그런 경우가 있어서 안되면 assert걸던가 ㅋ

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
		/// 무조건 찾아보고 없다고 리턴하게 되면 에러를 씹는게 되어 버림
		/// 그래서 잘못된 playerId가 들어 올 수 있는지부터 확인을 해야 함. 논리적으로 이런 경우가 생길 수 없는 경우라면, assert가 되어야 함
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
