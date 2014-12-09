#include "stdafx.h"
#include "ShootingSkill.h"
#include "Scheduler.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Missile.h"

ShootingSkill::ShootingSkill()
{
    m_MissileType = MS_NONE;
    m_MissileSpeed = 0.0f;
    m_MissileScale = 0.0f;
    m_MissileHp = 0;
    m_Range = 0.0f;
}


ShootingSkill::~ShootingSkill()
{
}

b2Vec2 ShootingSkill::GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto displacement = targetPos - heroPos;
    displacement.Normalize();
    displacement *= m_HeroBodySize + REDUCE(64);
    displacement += heroPos;
    return displacement;
}

void ShootingSkill::ShootMissile(b2Vec2 initPos)
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

void ShootingSkill::ShootMissileRepet(b2Vec2 initPos, int repetNum, int repetCycle)
{
    ShootMissile(initPos);

    if (--repetNum > 0)
    {
        CallFuncAfter(repetCycle, this, &ShootingSkill::ShootMissileRepet, initPos, repetNum, repetCycle);
    }
}
