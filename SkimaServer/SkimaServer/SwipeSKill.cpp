#include "stdafx.h"
#include "SwipeSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"


SwipeSkill::SwipeSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 75;
    m_Scale = Reduce(100.0f);
    m_Range = Reduce(120.0f);
}


SwipeSkill::~SwipeSkill()
{
}

void SwipeSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto direction = targetPos - heroPos;
    auto distance = direction.Normalize();
    auto attackPos = targetPos;
    if (distance > m_Range)
    {
        direction *= m_Range;
        attackPos = heroPos + direction;
    }

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, attackPos, key);

    hero->SetUnitHiddenState(false);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&SwipeSkill::FieldDamage, this, attackPos, Reduce(80.0f), m_Damage * hero->GetDamageBonus());
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->RepeatTimer(300, 3, func);
    game->PushTimer(timer);
}
