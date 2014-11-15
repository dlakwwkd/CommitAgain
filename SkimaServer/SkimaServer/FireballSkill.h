#pragma once
#include "ShootingSkill.h"

class FireballMissile;

class FireballSkill :
	public ShootingSkill
{
public:
	FireballSkill();
	virtual ~FireballSkill();

	void Shoot(int unitId, b2Vec2 targetPos);

private:
	FireballMissile*	ms_fireball;
};

