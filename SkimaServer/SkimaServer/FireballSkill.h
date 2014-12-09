#pragma once
#include "ShootingSkill.h"

class FireballSkill : public ShootingSkill
{
public:
    FireballSkill(Player* owner, float heroBodySize);
    virtual ~FireballSkill();

    virtual void SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos);

};

