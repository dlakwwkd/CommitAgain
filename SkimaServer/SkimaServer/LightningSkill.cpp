#include "stdafx.h"
#include "LightningSkill.h"
#include "ClientSession.h"
#include "Player.h"


LightningSkill::LightningSkill(Player* owner)
{
    m_Owner = owner;
}


LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->SetState(hero->GetStandbyState());

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), SKILL_W, heroPos, targetPos);
}
