#include "stdafx.h"
#include "TeleportSkill.h"
#include "ClientSession.h"
#include "Player.h"

TeleportSkill::TeleportSkill()
{
    m_Range = REDUCE(224);
}

TeleportSkill::TeleportSkill(Player* owner)
{
    m_Range = REDUCE(224);
    m_Owner = owner;
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto direction = targetPos - heroPos;
    auto distance = direction.Normalize();

    if (distance > m_Range)
    {
        direction *= m_Range;
        targetPos = heroPos + direction;
    }
    hero->GetBody()->SetTransform(targetPos, 0);

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), key, heroPos, targetPos);
}
