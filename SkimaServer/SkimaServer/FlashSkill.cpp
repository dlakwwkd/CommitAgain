#include "stdafx.h"
#include "FlashSkill.h"
#include "ClientSession.h"
#include "Player.h"


FlashSkill::FlashSkill()
{
}

FlashSkill::FlashSkill(Player* owner)
{
    m_Owner = owner;
}


FlashSkill::~FlashSkill()
{
}

void FlashSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->SetState(hero->GetStandbyState());

    auto displacement = targetPos - hero->GetBody()->GetPosition();
    if (displacement.Normalize() < 0.5f)
    {
        hero->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
        return;
    }
    displacement *= REDUCE(1200);
    hero->GetBody()->SetLinearVelocity(displacement);
}
