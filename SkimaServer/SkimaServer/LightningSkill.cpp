#include "stdafx.h"
#include "LightningSkill.h"
#include "ClientSession.h"
#include "Player.h"
#include "Game.h"
#include "Timer.h"


LightningSkill::LightningSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 62;
    m_Scale = Reduce(100.0f);
    m_Range = Reduce(300.0f);
}


LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
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

    auto game = m_Owner->GetGame();
    Timer::Push(game, 200, 5, this, &LightningSkill::FieldDamage, attackPos, m_Scale, m_Damage);
}
