#include "stdafx.h"
#include "FireballSkill.h"
#include "FireballMissile.h"
#include "Hero.h"

FireballSkill::FireballSkill(int playerid)
{
	m_PlayerId = playerid;
	m_MissileSpeed = 5.0f;
	m_Damage = 50;
	m_MissileLiveTime = 500.0f;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::ShootSkill(int unitId, b2Vec2 initPos, b2Vec2 targetPos)
{
	ms_fireball = new FireballMissile(m_PlayerId, unitId, initPos, targetPos);
	ms_fireball->SetMissileSpeed(m_MissileSpeed);
	ms_fireball->SetMissileDamage(m_Damage);
	ms_fireball->SetMissileLivetime(m_MissileLiveTime);
	ms_fireball->MissileShoot();
}
