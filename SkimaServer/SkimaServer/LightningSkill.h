#pragma once
#include "Skill.h"
class LightningSkill : public Skill
{
public:
    LightningSkill(Player* owner);
	virtual ~LightningSkill();

    virtual void SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos);
};

