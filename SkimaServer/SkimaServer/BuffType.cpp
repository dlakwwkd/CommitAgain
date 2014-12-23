#include "stdafx.h"
#include "BuffType.h"
#include "ClientSession.h"
#include "Player.h"
#include "Game.h"
#include "GameManager.h"


BuffType::BuffType()
{
    m_Duration = 0;
    m_Bonus = 0;
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
        hero->SetSpeed(hero->GetSpeed() + m_Bonus);

        auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
        auto func = std::bind(&BuffType::MoveSpeedBonusEnd, this);
        game->CallFuncOnce(m_Duration, func);

        auto client = m_Owner->GetClient();
        client->BuffBroadCast(hero->GetUnitID(), m_Bonus, BUFF_SPEED);
    }
}

void BuffType::MoveSpeedBonusEnd()
{
    if (m_IsOn)
    {
        m_IsOn = false;
        auto hero = m_Owner->GetMyHero();
        hero->SetSpeed(hero->GetSpeed() - m_Bonus);

        auto client = m_Owner->GetClient();
        client->BuffBroadCast(hero->GetUnitID(), (-m_Bonus), BUFF_SPEED);
    }
}
