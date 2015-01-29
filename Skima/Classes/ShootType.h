#pragma once
#include "Skill.h"
class ShootType : public Skill
{
public:
    ShootType();
    virtual ~ShootType();
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

