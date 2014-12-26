#pragma once
#include "Skill.h"
class ShortDashSkill : public Skill
{
public:
    ShortDashSkill(Hero* hero);
    virtual ~ShortDashSkill();

    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();

private:
    int m_DashCount;
};

