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
    auto func = std::bind(&WaveSystem::WaveProcess, this);
    auto timer = new Timer(m_Game->GetGameID());
    timer->RepeatTimer(100, 10, func);
    m_Game->PushTimer(timer);
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
    mob->SetSpeed(Reduce(100.0f));
    mob->SetDamage(20);
    mob->SetMaxHp(200);
    mob->SetHp(200);
    mob->ChaseEnemy();
    computer->GetClient()->CreateMobBroadCast(PT_COMPUTER, mob->GetUnitID(), m_RegenPos);
}
