#include "stdafx.h"
#include "FlashSkill.h"
#include "ClientSession.h"
#include "Player.h"


FlashSkill::FlashSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 100;
    m_Duration = 1000;
    m_Bonus = Reduce(1200.0f);
}


FlashSkill::~FlashSkill()
{
}

void FlashSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->Crashing(false);

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    MoveSpeedBonus();
    hero->TryMove(heroPos, targetPos);
}

void FlashSkill::CastStop(SkillKey key)
{
    MoveSpeedBonusEnd();
}
