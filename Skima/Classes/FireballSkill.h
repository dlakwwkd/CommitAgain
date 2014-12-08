#pragma once
#include "ShootType.h"
class FireballSkill : public ShootType
{
public:
    FireballSkill();
    FireballSkill(Hero* hero);
    virtual ~FireballSkill();

public:
    //virtual void SkillCast(Vec2 heroPos, Vec2 targetPos, int missileID);
//     virtual void SkillReady();
//     virtual void SkillEnd();
    
};

