#pragma once
#include "Skill.h"
class Buff : public Skill
{
public:
    Buff();
    virtual ~Buff();
    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

