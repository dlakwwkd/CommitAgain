#pragma once
#include "Skill.h"
class FlashSkill : public Skill
{
public:
    FlashSkill(Hero* hero);
    virtual ~FlashSkill();

    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

