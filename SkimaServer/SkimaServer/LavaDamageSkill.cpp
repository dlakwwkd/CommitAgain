#include "stdafx.h"
#include "LavaDamageSkill.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"


LavaDamageSkill::LavaDamageSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 10;
}


LavaDamageSkill::~LavaDamageSkill()
{
    if (m_Timer)
    {
        m_Timer->SetOff();
    }
}

void LavaDamageSkill::LavaDamage(b2Vec2 createPos, float scale, int damage, int repeatDelay)
{
    auto game = m_Owner->GetGame();
    Timer::Push(game, repeatDelay, TIMER_INFINITE, this, &LavaDamageSkill::FieldDamage, createPos, scale, damage);
}
