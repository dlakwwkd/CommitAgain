#pragma once
#include "ShootType.h"
class IceballSkill : public ShootType
{
public:
    IceballSkill();
    IceballSkill(Hero* hero);
    virtual ~IceballSkill();

public:
    //virtual void SkillCast(Vec2 heroPos, Vec2 targetPos, int missileID);
//     virtual void SkillReady();
//     virtual void SkillEnd();
};

