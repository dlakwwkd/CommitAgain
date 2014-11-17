#pragma once
#include "ShootingSkill.h"

class FireballMissile;

class FireballSkill : public ShootingSkill
{
public:
	FireballSkill(int playerid,float heroBodySize);
	virtual ~FireballSkill();

	virtual void SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos);

};

