#include "stdafx.h"
#include "FireballSkill.h"
#include "FireMissile.h"


FireballSkill::FireballSkill(int playerid)
{
	m_PlayerId = playerid;
	m_Speed = 5;
	m_Damage = 50;
	m_LiveTime = 500;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::Shoot(int unitId, b2Vec2 targetPos)
{
	ms_fireball = new FireballMissile(m_PlayerId, unitId);
	ms_fireball->SetVelocity(m_Speed);
	ms_fireball->SetDamage(m_Damage);
	ms_fireball->SetTargerPos(targetPos);
	ms_fireball->SetLiveTime(m_LiveTime);
	ms_fireball->Shoot();
}
