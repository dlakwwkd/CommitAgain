#include "stdafx.h"
#include "HideSkill.h"
#include "ClientSession.h"
#include "Game.h"
#include "Player.h"


HideSkill::HideSkill(Player* owner)
{
    m_Owner = owner;
    m_Duration = 5000;
    m_SpeedBonus = Reduce(500.0f);
}


HideSkill::~HideSkill()
{
}

void HideSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();
 
    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    HideSkillCast();
}
