#pragma once
#include "Skill.h"
class TeleportSkill :	public Skill
{
public:
    TeleportSkill();
    TeleportSkill(Hero* hero);
    ~TeleportSkill();

    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

