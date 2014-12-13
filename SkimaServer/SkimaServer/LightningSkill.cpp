#include "stdafx.h"
#include "LightningSkill.h"
#include "ClientSession.h"
#include "Player.h"


LightningSkill::LightningSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 75;
    m_Scale = REDUCE(100);
}


LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), key, heroPos, targetPos);

    FieldDamageRepeat(targetPos, m_Scale, m_Damage, 5, 200);
}
