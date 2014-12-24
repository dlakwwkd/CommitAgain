#include "stdafx.h"
#include "Mob.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"



Mob::Mob()
{
	static int makeId = 0;
	m_UnitID = SET_MAIN_TYPE(++makeId, UNIT_MOB);
}


Mob::~Mob()
{
    if (m_Timer)
    {
        m_Timer->SetOff();
    }
}

void Mob::ChaseEnemy()
{
    if (!m_Owner)
    {
        return;
    }
    m_Game = GGameManager->SearchGame(m_Owner->GetRoomID());
    m_Timer = new Timer(m_Owner->GetRoomID());

    auto func = std::bind(&Mob::Chasing, this);
    m_Timer->InfiniteTimer(1000, func);
    m_Game->PushTimer(m_Timer);
}

void Mob::Chasing()
{
    m_Game->Targeting(this);
    m_State->TryMove(this);
}