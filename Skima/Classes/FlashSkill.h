#pragma once
#include "Skill.h"
class FlashSkill : public Skill
{
public:
    FlashSkill();
    FlashSkill(Hero* hero);
    virtual ~FlashSkill();

    virtual void SkillReady();
    virtual void SkillEnd();
};

