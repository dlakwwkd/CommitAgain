#pragma once
#include "ShootType.h"

class FireballSkill : public ShootType
{
public:
    FireballSkill(Player* owner, float heroBodySize);
    virtual ~FireballSkill();

    virtual void SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos);

};

