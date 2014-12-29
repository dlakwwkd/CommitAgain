#include "stdafx.h"
#include "Game.h"
#include "GameRoom.h"
#include "GameManager.h"
#include "Player.h"
#include "Map.h"
#include "Rock.h"
#include "MoveRock.h"
#include "ClientSession.h"
#include "Scheduler.h"
#include "Mob.h"
#include "Timer.h"
#include "WaveSystem.h"


Game::Game(GameRoom* room)
{
	m_IsStart = false;
    m_GameID = room->m_RoomInfo.mRoomNum;
    m_LoadedPlayerNum = 0;

    for (auto& player : room->m_PlayerList)
    {
        m_PlayerList[player.first] = player.second;
    }
}

Game::~Game()
{
}

void Game::Tick(float dt)
{
    for (auto& player : m_PlayerList)
    {
        for (auto& unit : player.second->GetUnitList())
        {
            unit.second->Movement();
        }
    }
}

void Game::PushTimer(Timer* timer)
{
    auto iter = m_TimerList.find(timer->GetTimerId());
    if (iter == m_TimerList.end())
    {
        m_TimerList[timer->GetTimerId()] = timer;
    }
    else
    {
        printf(" - PushTimer Failed ! \n");
    }
}

void Game::PopTimer(int timerId)
{
    auto iter = m_TimerList.find(timerId);
    if (iter == m_TimerList.end())
    {
        printf(" - PopTimer Failed ! \n");
    }
    else
    {
        m_TimerList.erase(iter);
    }
}

void Game::InitGame()
{
    // 주의: 여기서부턴 하드코딩의 구간입니다.^^
    ClientSession* temp = nullptr;
    int roomId = -1;
    float i = Reduce(-100.0f);
    b2Vec2 createPos = { 0, 0 };
    for (auto& player : m_PlayerList)
    {
        if (i < 0.0f)
        {
            temp = player.second->GetClient();
        }
        i += Reduce(100.0f);
        roomId = player.second->GetRoomID();
        switch (player.second->GetTeam())
        {
        case TEAM_A:    createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 2 + i };                         break;
        case TEAM_B:    createPos = { MAX_MAP_SIZE_X / 4 + MAX_MAP_SIZE_X / 2, MAX_MAP_SIZE_Y / 2 + i };    break;
        default:
            break;
        }
        player.second->CreateHero(CONVERT_IN(createPos, roomId));
    }
    m_Computer = new Player(temp, PT_COMPUTER, "Computer", PT_COMPUTER);
    m_Computer->SetRoomID(roomId);
    m_Computer->SetTeam(TEAM_C);
	m_PlayerList[PT_COMPUTER] = m_Computer;

    m_Map = new Map(roomId);
    m_Map->InitMap(m_Computer, roomId);

    temp->ServerRunComplete();
}

void Game::StartGame()
{
    m_IsStart = true;

    auto func = std::bind(&Map::LavaCreate, m_Map, m_Computer, m_GameID);
    auto timer = new Timer(m_GameID);
    timer->RepeatTimer(10000, 10, func);
    PushTimer(timer);

    m_WaveSystem = new WaveSystem(this);
    auto func2 = std::bind(&WaveSystem::WaveLoop, m_WaveSystem);
    auto timer2 = new Timer(m_GameID);
    timer2->InfiniteTimer(30000, func2);
    PushTimer(timer2);
}

void Game::EndGame()
{
	m_IsStart = false;

    for (auto& timer : m_TimerList)
    {
        timer.second->SetOff();
    }
    delete m_Map;
    delete m_WaveSystem;

    auto computer = m_PlayerList.find(PT_COMPUTER);
    if (computer != m_PlayerList.end())
    {
        computer->second->UnitListClear();
        delete computer->second;
        m_PlayerList.erase(computer);
    }
    for (auto& player : m_PlayerList)
    {
        player.second->SetTeam(TEAM_N);
        player.second->UnitListClear();
    }
}


Player* Game::GetPlayer(int playerId)
{
    if (playerId < 0)
    {
        printf(" - GetPlayer Failed ! : playerId is invalid \n");
        return nullptr;
    }
    auto player = m_PlayerList.find(playerId);
    if (player == m_PlayerList.end())
    {
        printf(" - GetPlayer Failed ! : relevant player isn't \n");
        return nullptr;
    }
    return player->second;
}

void Game::OutPlayer(int playerId)
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

    player->second->SetTeam(TEAM_N);
    player->second->UnitListClear();
    m_PlayerList.erase(player);

    printf("\n [Out  Game] Game ID %d, Player ID: %d \n", m_GameID, playerId);
}


void Game::Targeting(Unit* caster)
{
    if (!m_IsStart)
    {
        return;
    }
    auto curPos = caster->GetBody()->GetPosition();
    float distance = 0;
    b2Vec2 targetPos = { 0, 0 };

    if (rand() % 3 == 0)
    {
        for (auto& player : m_PlayerList)
        {
            if (player.second->GetTeam() == caster->GetOwner()->GetTeam())
            {
                continue;
            }
            auto enemy = player.second->GetMyHero();
            if (enemy == nullptr)
            {
                continue;
            }
            auto enemyPos = enemy->GetBody()->GetPosition();
            auto displacement = enemyPos - curPos;
            auto length = displacement.Length();

            if (length > distance)
            {
                distance = length;
                targetPos = enemyPos;
            }
        }
    }
    else
    {
        targetPos.x = curPos.x + static_cast<float>(rand() % 200 - 100);
        targetPos.y = curPos.y + static_cast<float>(rand() % 200 - 100);
    }
    caster->SetTargetPos(targetPos);
}

