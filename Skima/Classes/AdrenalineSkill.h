#pragma once
#include "Skill.h"
class AdrenalineSkill : public Skill
{
public:
    AdrenalineSkill();
    AdrenalineSkill(Hero* hero);
    virtual ~AdrenalineSkill();

    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

