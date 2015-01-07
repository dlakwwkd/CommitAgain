#include "stdafx.h"
#include "Game.h"
#include "GameRoom.h"
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

void Game::InitGame(RoomType roomType)
{
    // 주의: 여기서부턴 하드코딩의 구간입니다.^^
    ClientSession* temp = nullptr;
    int roomId = -1;
    float i = 150.0f;
    float j = -150.0f;
    int num = 1;
    b2Vec2 createPos = { 0, 0 };
    for (auto& player : m_PlayerList)
    {
        player.second->SetGame(this);
        player.second->InitGameOverStatus();
        if (roomType == ROOM_MELEE)
        {
            player.second->SetTeam(Team(++num));
        }

        if (num <= 2)
        {
            temp = player.second->GetClient();
        }
        roomId = player.second->GetRoomID();
        //Team에 따라 생성위치 설정
        switch (player.second->GetTeam())
        {
        case TEAM_1:    createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 6 + i };                             i += 150.0f;   break;
        case TEAM_2:    createPos = { MAX_MAP_SIZE_X / 4 + MAX_MAP_SIZE_X / 2, MAX_MAP_SIZE_Y * 5 / 6 + j };    j -= 150.0f;   break;
        case TEAM_3:    createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 6 + i };                             i += 150.0f;   break;
        case TEAM_4:    createPos = { MAX_MAP_SIZE_X / 4 + MAX_MAP_SIZE_X / 2, MAX_MAP_SIZE_Y * 5 / 6 + j };    j -= 150.0f;   break;
        case TEAM_5:    createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 6 + i };                             i += 150.0f;   break;
        case TEAM_6:    createPos = { MAX_MAP_SIZE_X / 4 + MAX_MAP_SIZE_X / 2, MAX_MAP_SIZE_Y * 5 / 6 + j };    j -= 150.0f;   break;
        case TEAM_7:    createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 6 + i };                             i += 150.0f;   break;
        case TEAM_8:    createPos = { MAX_MAP_SIZE_X / 4 + MAX_MAP_SIZE_X / 2, MAX_MAP_SIZE_Y * 5 / 6 + j };    j -= 150.0f;   break;
        default:
            break;
        }
        player.second->CreateHero(CONVERT_IN(createPos, roomId), roomType);
    }
    m_Computer = new Player(temp, "Computer", PT_COMPUTER);
    m_Computer->SetRoomID(roomId);
    m_Computer->SetTeam(TEAM_C);
    m_Computer->SetGame(this);
	m_PlayerList[PT_COMPUTER] = m_Computer;

    m_Map = new Map(roomId);
    m_Map->InitMap(m_Computer, roomId);

    temp->ServerRunComplete();
}

void Game::StartGame()
{
    m_IsStart = true;

    m_WaveSystem = new WaveSystem(this);
    Timer::Push(this, 30000, TIMER_INFINITE, m_WaveSystem, &WaveSystem::WaveLoop);
    Timer::Push(this, 10000, 10, m_Map, &Map::LavaCreate, m_Computer, m_GameID);
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
        player.second->SetGame(nullptr);
        player.second->SetTeam(TEAM_N);
        player.second->UnitListClear();
    }
}

bool Game::DecideWinTeam(OUT Team& winTeam)
{
    int surviveTeamNum = 0;
    winTeam = TEAM_C;
    for (auto& iter : m_PlayerList)
    {
        auto otherPlayer = iter.second;
        if (otherPlayer->IsGameOver() || otherPlayer->GetTeam() == winTeam)
        {
            continue;
        }
        ++surviveTeamNum;
        winTeam = otherPlayer->GetTeam();
    }

    if (surviveTeamNum > 1)
    {
        return false;
    }
    return true;
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

