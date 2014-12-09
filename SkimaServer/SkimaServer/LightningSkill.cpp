#include "stdafx.h"
#include "LightningSkill.h"
#include "Player.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"


LightningSkill::LightningSkill(Player* owner)
{
    m_Owner = owner;
}


LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->SetState(hero->GetStandbyState());

    auto client = GClientManager->GetClient(m_Owner->GetPlayerID());
    client->SkillBroadCast(hero->GetUnitID(), skillType, SKILL_W, heroPos, targetPos);
}
