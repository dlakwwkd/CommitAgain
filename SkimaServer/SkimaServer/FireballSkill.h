#pragma once
#include "ShootingSkill.h"

class FireballSkill : public ShootingSkill
{
public:
    FireballSkill(int playerid,float heroBodySize);
    virtual ~FireballSkill();

    virtual void SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos);

};

