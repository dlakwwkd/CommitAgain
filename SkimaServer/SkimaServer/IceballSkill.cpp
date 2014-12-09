#include "stdafx.h"
#include "IceballSkill.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Missile.h"

IceballSkill::IceballSkill(Player* owner, float heroBodySize)
{
    m_Owner = owner;
    m_Damage = 400;
    m_MissileType = MS_ICE_BALL;
    m_MissileSpeed = REDUCE(800);
    m_MissileScale = DEF_SCALE;
    m_HeroBodySize = heroBodySize;
    m_Range = REDUCE(800);
    m_MissileHp = 100;
}


IceballSkill::~IceballSkill()
{
}

void IceballSkill::SkillCast(b2Vec2 heroPos, b2Vec2 targetPos)
{
    m_TargetPos = targetPos;
    ShootMissile(GenerateInitPos(heroPos, targetPos));
}
