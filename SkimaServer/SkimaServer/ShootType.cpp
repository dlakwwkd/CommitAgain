#include "stdafx.h"
#include "ShootType.h"
#include "Scheduler.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Missile.h"

ShootType::ShootType()
{
    m_MissileType = MS_NONE;
    m_MissileSpeed = 0.0f;
    m_MissileScale = 0.0f;
    m_MissileHp = 0;
    m_Range = 0.0f;
}


ShootType::~ShootType()
{
}

b2Vec2 ShootType::GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto displacement = targetPos - heroPos;
    displacement.Normalize();
    displacement *= m_HeroBodySize + REDUCE(64);
    displacement += heroPos;
    return displacement;
}

void ShootType::ShootMissile(b2Vec2 initPos)
{
    auto missile = static_cast<Missile*>(GObjectManager->Assign(UNIT_MISSILE));
    m_Owner->UnitListPush(missile->GetUnitID(), missile);

    missile->SetMissileInit(m_Owner, m_MissileType, initPos, m_MissileScale);
    missile->SetMissileTargetPos(m_TargetPos);
    missile->SetMissileSpeed(m_MissileSpeed);
    missile->SetMissileDamage(m_Damage);
    missile->SetMissileRange(m_Range);
    missile->SetMissileHp(m_MissileHp);
    missile->MissileShoot();
}

void ShootType::ShootMissileRepet(b2Vec2 initPos, int repetNum, int repetCycle)
{
    ShootMissile(initPos);

    if (--repetNum > 0)
    {
        CallFuncAfter(repetCycle, this, &ShootType::ShootMissileRepet, initPos, repetNum, repetCycle);
    }
}
