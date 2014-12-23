#include "stdafx.h"
#include "FlashSkill.h"
#include "ClientSession.h"
#include "Player.h"


FlashSkill::FlashSkill(Player* owner)
{
    m_Owner = owner;
}


FlashSkill::~FlashSkill()
{
}

void FlashSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->Crashing(false);
    hero->SetTargetPos(targetPos);
    hero->GetState()->TryMove(hero);

    auto displacement = targetPos - hero->GetBody()->GetPosition();
    if (displacement.Normalize() < 0.5f)
    {
        return;
    }
    displacement *= Reduce(1500.0f);
    hero->GetBody()->SetLinearVelocity(displacement);

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
}
