#include "stdafx.h"
#include "LavaDamageSkill.h"
#include "GameManager.h"
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
    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&LavaDamageSkill::FieldDamage, this, createPos, scale, damage);
    m_Timer = new Timer(m_Owner->GetRoomID());
    m_Timer->InfiniteTimer(repeatDelay, func);
    game->PushTimer(m_Timer);
}
