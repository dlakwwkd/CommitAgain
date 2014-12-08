#pragma once
#include "Skill.h"
class ShootType : public Skill
{
public:
    ShootType();
    virtual ~ShootType();

    virtual void SkillReady();
    virtual void SkillEnd();
};

