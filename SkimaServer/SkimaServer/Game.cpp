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


Game::Game(GameRoom* room)
{
	m_IsStart = false;
    m_GameID = room->m_RoomID;
    m_LoadedPlayerNum = 0;

    for (auto& player : room->m_PlayerList)
    {
        m_PlayerList[player.first] = player.second;
    }
}

Game::~Game()
{
    auto computer = m_PlayerList.find(PT_COMPUTER);
    if (computer != m_PlayerList.end())
    {
        computer->second->UnitListClear();
        delete computer->second;
        m_PlayerList.erase(computer);
    }
    delete m_Map;

    for (auto& player : m_PlayerList)
    {
        player.second->SetTeam(TEAM_N);
        player.second->UnitListClear();
    }
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
        printf(" - PushTimer : curNum: %d \n", m_TimerList.size());
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
        printf(" - PopTimer : curNum: %d \n", m_TimerList.size());
    }
}

void Game::InitGame()
{
    IncRefCount();

    // 주의: 여기서부턴 하드코딩의 구간입니다.^^
    ClientSession* temp = nullptr;
    int i = 0;
    int roomId = -1;
    for (auto& player : m_PlayerList)
    {
        player.second->SetTeam(TEAM_A);
        b2Vec2 createPos = { MAX_MAP_SIZE_X / 4, MAX_MAP_SIZE_Y / 2 };
        roomId = player.second->GetRoomID();
        if (++i == 2)
        {
            player.second->SetTeam(TEAM_B);
            createPos.x += MAX_MAP_SIZE_X / 2;
            temp = player.second->GetClient();
        }
        player.second->CreateHero(CONVERT_IN(createPos, roomId));
    }
    m_Computer = new Player(temp, PT_COMPUTER, "Computer", PT_COMPUTER);// 100번 보면 이해됨.
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
    timer->InfiniteTimer(6000, func);
    PushTimer(timer);
    
    MobWaveSystem();
    ChaseEnemy();
}

void Game::EndGame()
{
	m_IsStart = false;
    DecRefCount();

    for (auto& timer : m_TimerList)
    {
        timer.second->SetOff();
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

void Game::MobWaveSystem()
{
    if (!m_IsStart)
    {
        return;
    }
    b2Vec2 createPos = { MAX_MAP_SIZE_X / 2, MAX_MAP_SIZE_Y - 100 };
    createPos = CONVERT_IN(createPos, m_GameID);

    auto mob = new Mob();
    mob->SetDynamicBody(m_Computer, MOB_PEA, createPos, DEF_SCALE);
    mob->SetSpeed(Reduce(200.0f));
    mob->SetDamage(20);
    mob->SetMaxHp(200);
    mob->SetHp(200);
    m_Computer->GetClient()->CreateMobBroadCast(PT_COMPUTER, mob->GetUnitID(), createPos);

    CallFuncAfter(5000, this, &Game::MobWaveSystem);
}

void Game::ChaseEnemy()
{
    if (!m_IsStart)
    {
        return;
    }
    for (auto& unit : m_Computer->GetUnitList())
    {
        if (GET_MAIN_TYPE(unit.second->GetUnitID()) == UNIT_MOB)
        {
            unit.second->Chasing();
        }
    }
    CallFuncAfter(1000, this, &Game::ChaseEnemy);
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

    if (rand() % 2 == 0)
    {
        for (auto& player : m_PlayerList)
        {
            if (player.second->GetTeam() == caster->GetOwner()->GetTeam())
            {
                continue;
            }
            auto temp = player.second->GetMyHero()->GetBody()->GetPosition();
            auto temp2 = temp - curPos;
            auto temp3 = temp.Length();

            if (temp3 > distance)
            {
                distance = temp3;
                targetPos = temp;
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

