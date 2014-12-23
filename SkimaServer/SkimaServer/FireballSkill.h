#pragma once
#include "ShootType.h"

class FireballSkill : public ShootType
{
public:
    FireballSkill(Player* owner, float heroBodySize);
    virtual ~FireballSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void CastStop(SkillKey key){}

};

