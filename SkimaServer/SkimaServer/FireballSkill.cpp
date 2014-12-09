﻿#include "stdafx.h"
#include "FireballSkill.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Missile.h"

FireballSkill::FireballSkill(Player* owner, float heroBodySize)
{
    m_Owner = owner;
    m_Damage = 600;
    m_MissileSpeed = REDUCE(1200);
    m_MissileLiveTime = 500.0f;
    m_HeroBodySize = heroBodySize;
    m_Range = REDUCE(800);
    m_Hp = 100;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos)
{
    b2Vec2 initPos = GenerateInitPos(heroPos, targetPos);

    auto missile = static_cast<Missile*>(GObjectManager->Assign(UNIT_MISSILE));
    m_Owner->UnitListPush(missile->GetUnitID(), missile);

    missile->SetMissileInit(m_Owner, MS_FIRE_BALL, initPos, DEF_SCALE);
    missile->SetMissileTargetPos(targetPos);
    missile->SetMissileSpeed(m_MissileSpeed);
    missile->SetMissileDamage(m_Damage);
    missile->SetMissileLivetime(m_MissileLiveTime);
    missile->SetMissileRange(m_Range);
    missile->SetMissileHp(m_Hp);
    missile->MissileShoot();
}
