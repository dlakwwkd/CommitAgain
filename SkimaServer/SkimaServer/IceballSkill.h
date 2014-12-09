#pragma once
#include "ShootingSkill.h"
class IceballSkill : public ShootingSkill
{
public:
    IceballSkill(Player* owner, float heroBodySize);
    virtual~IceballSkill();

    virtual void SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos);

};

