#pragma once
#include "Skill.h"
class HideSkill : public Skill
{
public:
    HideSkill(Hero* hero);
    virtual ~HideSkill();

    virtual void    SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void    SkillReady();
    virtual void    SkillEnd();

private:
    int             m_HiddenTime;
};

