#include "stdafx.h"
#include "FireballSkill.h"
#include "FireMissile.h"


FireballSkill::FireballSkill()
{
	m_Speed = 5;
	m_Damage = 50;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::Shoot(b2Vec2 targetPos)
{
	ms_fireball = new FireballMissile;
	ms_fireball->SetVelocity(m_Speed);
	ms_fireball->SetDamage(m_Damage);
	ms_fireball->SetTargerPos(targetPos);
	ms_fireball->Shoot();
}
