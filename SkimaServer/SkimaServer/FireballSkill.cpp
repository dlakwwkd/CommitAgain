#include "stdafx.h"
#include "FireballSkill.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Missile.h"

FireballSkill::FireballSkill(Player* owner, float heroBodySize)
{
    m_Owner = owner;
    m_Damage = 600;
    m_MissileType = MS_FIRE_BALL;
    m_MissileSpeed = REDUCE(1200);
    m_MissileScale = DEF_SCALE;
    m_HeroBodySize = heroBodySize;
    m_Range = REDUCE(800);
    m_MissileHp = 100;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
    m_TargetPos = targetPos;
    ShootMissile(GenerateInitPos(heroPos, targetPos));
}
