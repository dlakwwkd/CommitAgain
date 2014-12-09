#pragma once
#include "ShootingSkill.h"
class SparkSkill : public ShootingSkill
{
public:
    SparkSkill(Player* owner, float heroBodySize);
	virtual ~SparkSkill();

	virtual void SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos);
};

