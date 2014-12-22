#include "stdafx.h"
#include "ShootType.h"
#include "Scheduler.h"
#include "Player.h"
#include "Missile.h"

ShootType::ShootType()
{
    m_MissileType = MS_NONE;
    m_MissileSpeed = 0.0f;
    m_MissileScale = 0.0f;
    m_MissileHp = 0;
}


ShootType::~ShootType()
{
}

b2Vec2 ShootType::GenerateInitPos(const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto displacement = targetPos - heroPos;
    displacement.Normalize();
    displacement *= m_HeroBodySize + REDUCE(64);
    displacement += heroPos;
    return displacement;
}

void ShootType::ShootMissile(const b2Vec2& initPos)
{
    auto missile = new Missile();

    missile->SetDynamicBody(m_Owner, m_MissileType, initPos, m_MissileScale);
    missile->SetTargetPos(m_TargetPos);
    missile->SetSpeed(m_MissileSpeed);
    missile->SetDamage(m_Damage);
    missile->SetRange(m_Range);
	missile->SetMaxHp(m_MissileHp);
	missile->SetHp(m_MissileHp);
    missile->MissileShoot();
}