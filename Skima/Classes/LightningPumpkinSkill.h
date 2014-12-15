#pragma once
#include "Skill.h"

class Hero;
class LightningPumpkinSkill : public Skill
{
public:
    LightningPumpkinSkill();
    LightningPumpkinSkill(Hero* hero);
    virtual ~LightningPumpkinSkill();

    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

