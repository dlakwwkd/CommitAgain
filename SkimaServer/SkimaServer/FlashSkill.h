#pragma once
#include "Skill.h"
class FlashSkill : public Skill
{
public:
    FlashSkill();
    FlashSkill(int playerID);
    virtual ~FlashSkill();

    virtual void SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos);

};

