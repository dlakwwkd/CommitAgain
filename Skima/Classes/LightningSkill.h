#pragma once
#include "Skill.h"
class Hero;

class LightningSkill : public Skill
{
public:
    LightningSkill(Hero* hero);
    virtual ~LightningSkill();

    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();
};

