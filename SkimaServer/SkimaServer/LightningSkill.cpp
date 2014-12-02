#include "stdafx.h"
#include "LightningSkill.h"
#include "Player.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"


LightningSkill::LightningSkill(int playerId)
{
    m_PlayerId = playerId;
}


LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = GGameManager->SearchPlayer(m_PlayerId)->GetMyHero();
    hero->SetState(hero->GetStandbyState());

    auto client = GClientManager->GetClient(m_PlayerId);
    client->SplashSkillBroadCast(hero->GetUnitID(), SKILL_W, heroPos, targetPos);
}
