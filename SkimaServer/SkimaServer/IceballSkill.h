#pragma once
#include "ShootType.h"
class IceballSkill : public ShootType
{
public:
    IceballSkill(Player* owner, float heroBodySize);
    virtual~IceballSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);

};

