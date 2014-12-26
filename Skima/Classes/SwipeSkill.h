#pragma once
#include "Skill.h"
class Hero;

class SwipeSkill : public Skill
{
public:
    SwipeSkill(Hero* hero);
    virtual ~SwipeSkill();

    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

