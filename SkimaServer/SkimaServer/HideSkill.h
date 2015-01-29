#pragma once
#include "BuffType.h"
class HideSkill : public BuffType
{
public:
    HideSkill(Player* owner);
    virtual ~HideSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void CastStop(){}

};

