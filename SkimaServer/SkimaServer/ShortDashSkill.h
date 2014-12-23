#pragma once
#include "BuffType.h"
class ShortDashSkill : public BuffType
{
public:
    ShortDashSkill(Player* owner);
    virtual ~ShortDashSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void CastStop();

};

