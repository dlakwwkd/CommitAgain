#pragma once
#include "Skill.h"
class FlashSkill : public Skill
{
public:
    FlashSkill();
    FlashSkill(Player* owner);
    virtual ~FlashSkill();

    virtual void SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos);

};

