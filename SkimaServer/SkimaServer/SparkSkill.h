#pragma once
#include "ShootType.h"
class SparkSkill : public ShootType
{
public:
    SparkSkill(Player* owner, float heroBodySize);
	virtual ~SparkSkill();

	virtual void SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos);
};

