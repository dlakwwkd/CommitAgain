#pragma once
#include "ShootingSkill.h"

class FireballMissile;

class FireballSkill : public ShootingSkill
{
public:
	FireballSkill(int playerid);
	virtual ~FireballSkill();

	virtual void ShootSkill(int unitId, b2Vec2 initPos, b2Vec2 targetPos);

private:
	FireballMissile*	ms_fireball;
};

