#pragma once
#include "Skill.h"

class Hero;
class LightningPumpkinSkill : public Skill
{
public:
    LightningPumpkinSkill();
    LightningPumpkinSkill(Hero* hero);
    virtual ~LightningPumpkinSkill();
};

