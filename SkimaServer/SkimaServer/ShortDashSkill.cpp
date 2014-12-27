#include "stdafx.h"
#include "ShortDashSkill.h"
#include "ClientSession.h"
#include "Player.h"


ShortDashSkill::ShortDashSkill(Player* owner)
{
    m_Owner = owner;
    m_Duration = 500;
    m_SpeedBonus = Reduce(750.0f);
}


ShortDashSkill::~ShortDashSkill()
{
}

void ShortDashSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();
    hero->EndCrash();

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    DashSkillCast();
    hero->TryMove(heroPos, targetPos);
}

void ShortDashSkill::CastStop()
{
    DashSkillEnd();
}
