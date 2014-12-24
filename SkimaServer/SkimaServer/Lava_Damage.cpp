#include "stdafx.h"
#include "Lava_Damage.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"


Lava_Damage::Lava_Damage(Player* owner)
{
    m_Owner = owner;
    m_Damage = 10;
}


Lava_Damage::~Lava_Damage()
{
    if (m_Timer)
    {
        m_Timer->SetOff();
    }
}

void Lava_Damage::LavaDamage(b2Vec2 createPos, float scale, int damage, int repeatDelay)
{
    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&Lava_Damage::FieldDamage, this, createPos, scale, damage);
    m_Timer = new Timer(m_Owner->GetRoomID());
    m_Timer->InfiniteTimer(repeatDelay, func);
    game->PushTimer(m_Timer);
}
