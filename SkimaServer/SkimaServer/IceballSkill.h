#pragma once
#include "ShootingSkill.h"
class IceballSkill : public ShootingSkill
{
public:
	IceballSkill(int playerid, float heroBodySize);
	virtual~IceballSkill();

	virtual void SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos);

};

