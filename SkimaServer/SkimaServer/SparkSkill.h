#pragma once
#include "ShootType.h"
class SparkSkill : public ShootType
{
public:
    SparkSkill(Player* owner, float heroBodySize);
	virtual ~SparkSkill();

	virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void CastStop(SkillKey key){}
};

