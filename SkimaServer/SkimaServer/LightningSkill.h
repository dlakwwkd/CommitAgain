#pragma once
#include "Skill.h"
class LightningSkill : public Skill
{
public:
    LightningSkill(int playerId);
	virtual ~LightningSkill();

    virtual void SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos);
};

