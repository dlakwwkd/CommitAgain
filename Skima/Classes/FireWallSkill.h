#pragma once
#include "Skill.h"
class Hero;

class FireWallSkill : public Skill
{
public:
    FireWallSkill(Hero* hero);
    virtual ~FireWallSkill();

    virtual void SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillCast(Vec2 heroPos, Vec2 targetPos);
    virtual void SkillReady();
    virtual void SkillEnd();

    Direction    GenerateWallDirection(Vec2 heroPos, Vec2 targetPos);
};

