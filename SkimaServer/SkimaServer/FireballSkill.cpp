#include "stdafx.h"
#include "FireballSkill.h"
#include "ClientSession.h"
#include "Player.h"
#include "Missile.h"

FireballSkill::FireballSkill(Player* owner, float heroBodySize)
{
    m_Owner = owner;
    m_Damage = 400;
    m_MissileType = MS_FIRE_BALL;
    m_MissileSpeed = REDUCE(1200);
    m_MissileScale = DEF_SCALE;
    m_HeroBodySize = REDUCE(heroBodySize);
    m_Range = REDUCE(800);
    m_MissileHp = 100;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    m_TargetPos = targetPos;
    ShootMissile(GenerateInitPos(heroPos, targetPos));

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
}
