#pragma once
#include "Skill.h"
class Hero;

class FireballSkill : public Skill
{
public:
    FireballSkill();
    FireballSkill(Hero* hero);
    virtual ~FireballSkill();

public:
    //virtual void SkillCast(Vec2 heroPos, Vec2 targetPos, int missileID);
    virtual void SkillReady();
    virtual void SkillEnd();
    
};

