#include "stdafx.h"
#include "FlashSkill.h"
#include "Player.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"


FlashSkill::FlashSkill()
{
}

FlashSkill::FlashSkill(int playerID)
{
    m_PlayerId = playerID;
}


FlashSkill::~FlashSkill()
{
}

void FlashSkill::SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = GGameManager->SearchPlayer(m_PlayerId)->GetMyHero();
    hero->SetState(hero->GetStandbyState());

    auto client = GClientManager->GetClient(m_PlayerId);
    client->SkillBroadCast(hero->GetUnitID(), skillType, SKILL_E, heroPos, targetPos);

    auto displacement = targetPos - hero->GetBody()->GetPosition();
    if (displacement.Normalize() < 0.5f)
    {
        hero->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
        return;
    }
    displacement *= hero->GetSpeed();
    hero->GetBody()->SetLinearVelocity(displacement);
}
