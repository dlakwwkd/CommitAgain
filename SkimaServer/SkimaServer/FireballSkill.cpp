#include "stdafx.h"
#include "FireballSkill.h"
#include "FireMissile.h"
#include "ClientSession.h"
#include "ClientManager.h"


FireballSkill::FireballSkill()
{
	m_Speed = 5;
	m_Damage = 50;
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
	ms_fireball->Shoot();
}
