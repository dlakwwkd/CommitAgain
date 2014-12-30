#include "stdafx.h"
#include "FireballSkill.h"
#include "ClientSession.h"
#include "Player.h"
#include "Missile.h"

FireballSkill::FireballSkill(Player* owner, float heroBodySize)
{
    m_Owner = owner;
    m_Damage = 64;
    m_MissileType = MS_FIRE_BALL;
    m_MissileSpeed = Reduce(1000.0f);
    m_MissileScale = DEF_SCALE;
    m_HeroBodySize = Reduce(heroBodySize);
    m_Range = Reduce(800.0f);
    m_MissileHp = 1000;
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
