#include "stdafx.h"
#include "WaveSystem.h"
#include "Map.h"
#include "Timer.h"
#include "Game.h"
#include "Mob.h"
#include "Player.h"
#include "ClientSession.h"


WaveSystem::WaveSystem(Game* game)
{
    m_Game = game;
    m_RegenPos = { MAX_MAP_SIZE_X / 2, MAX_MAP_SIZE_Y - 100 };
    m_RegenPos = CONVERT_IN(m_RegenPos, m_Game->GetGameID());
    m_WaveNum = 0;
}


WaveSystem::~WaveSystem()
{
}

void WaveSystem::WaveLoop()
{
    if (!m_Game->IsStart())
    {
        return;
    }
    ++m_WaveNum;
    Timer::Push(m_Game, 100, 10, this, &WaveSystem::WaveProcess);
}

void WaveSystem::WaveProcess()
{
    if (!m_Game->IsStart())
    {
        return;
    }
    auto computer = m_Game->GetPlayer(PT_COMPUTER);
    auto mob = new Mob();
    mob->SetDynamicBody(computer, MOB_PEA, m_RegenPos, DEF_SCALE);
    mob->SetSpeed(Reduce(100.0f + m_WaveNum*5));
    mob->SetDamage(20 + m_WaveNum);
    mob->SetMaxHp(200 + m_WaveNum*20);
    mob->SetHp(mob->GetMaxHp());
    mob->ChaseEnemy();
    computer->GetClient()->CreateMobBroadCast(PT_COMPUTER, mob->GetUnitID(), m_RegenPos, mob->GetMaxHp(), mob->GetSpeed());
}
