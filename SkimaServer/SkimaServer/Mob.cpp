#include "stdafx.h"
#include "Mob.h"
#include "ClientSession.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"
#include "Item.h"


Mob::Mob()
{
    m_UnitID = SET_MAIN_TYPE(MakeID(this), UNIT_MOB);
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
    m_Game = m_Owner->GetGame();
    m_Timer = Timer::Push(m_Game, 3000, TIMER_INFINITE, this, &Mob::Chasing);
}

void Mob::Chasing()
{
    m_Game->Targeting(this);
    m_State->TryMove(this);
}

void Mob::Dead()
{
    auto client = m_Owner->GetClient();
    auto gamble = rand() % 20;
    if (gamble < 3)
    {
        auto item = new Item(this, BUFF_SPEED); 
    }
    else if (gamble < 6)
    {
        auto item = new Item(this, BUFF_HP);
    }
    else if (gamble < 8)
    {
        auto item = new Item(this, BUFF_SHIELD);
    }
    else if (gamble < 9)
    {
        auto item = new Item(this, BUFF_DAMAGE);
    }
    else if (gamble < 10)
    {
        auto item = new Item(this, BUFF_COOLTIME);
    }
}
