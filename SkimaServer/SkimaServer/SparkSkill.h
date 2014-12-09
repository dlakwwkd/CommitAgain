#pragma once
#include "ShootingSkill.h"
class SparkSkill : public ShootingSkill
{
public:
    SparkSkill(Player* owner, float heroBodySize);
	virtual ~SparkSkill();

	virtual void SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos);
};

