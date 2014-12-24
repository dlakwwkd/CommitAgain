#include "stdafx.h"
#include "BuffType.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"


BuffType::BuffType()
{
    m_Duration = 0;
    m_SpeedBonus = 0;
}


BuffType::~BuffType()
{
}

void BuffType::MoveSpeedBonus()
{
    if (!m_IsOn)
    {
        m_IsOn = true;
        auto hero = m_Owner->GetMyHero();
        hero->SetSpeed(hero->GetSpeed() + m_SpeedBonus);
        hero->SetDamage(hero->GetDamage() + m_Damage);

        auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
        auto func = std::bind(&BuffType::MoveSpeedBonusEnd, this);
        auto timer = new Timer(m_Owner->GetRoomID());
        timer->CallFuncOnce(m_Duration, func);
        game->PushTimer(timer);

        auto client = m_Owner->GetClient();
        client->BuffBroadCast(hero->GetUnitID(), m_SpeedBonus, BUFF_SPEED);
    }
}

void BuffType::MoveSpeedBonusEnd()
{
    if (m_IsOn)
    {
        m_IsOn = false;
        auto hero = m_Owner->GetMyHero();
        hero->SetSpeed(hero->GetSpeed() - m_SpeedBonus);
        hero->SetDamage(hero->GetDamage() - m_Damage);
        hero->EndMove();
        hero->CurPosSync();

        auto client = m_Owner->GetClient();
        client->BuffBroadCast(hero->GetUnitID(), (-m_SpeedBonus), BUFF_SPEED);
    }
}
