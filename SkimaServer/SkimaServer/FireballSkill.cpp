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

void FireballSkill::ShootSkill(int unitId, b2Vec2 heroPos, b2Vec2 targetPos)
{
	//hero Pos�� �޾Ƽ� initPos�� �ٲ۴�.
	b2Vec2 initPos = GenerateInitPos(heroPos, targetPos); //todo : ������� ������ ������ ����
	int missileId = MakeMissileUnitId(unitId);

	ms_Fireball = new FireballMissile(m_PlayerId, missileId, initPos, targetPos);
	ms_Fireball->SetMissileSpeed(m_MissileSpeed);
	ms_Fireball->SetMissileDamage(m_Damage);
	ms_Fireball->SetMissileLivetime(m_MissileLiveTime);
	ms_Fireball->MissileShoot();
}
