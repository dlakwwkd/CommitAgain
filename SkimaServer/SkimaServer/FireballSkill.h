#pragma once
#include "ShootingSkill.h"

class FireballMissile;

class FireballSkill : public ShootingSkill
{
public:
	FireballSkill(int playerid,float heroBodySize);
	~FireballSkill();

	void SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos);

};

