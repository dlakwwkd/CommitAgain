#pragma once
#include "Skill.h"

class Hero;
class LightningSkill : public Skill
{
public:
    LightningSkill();
    LightningSkill(Hero* hero);
    virtual ~LightningSkill();

public:
    virtual void SkillReady();
    virtual void SkillEnd();
};

