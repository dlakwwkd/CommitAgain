#pragma once
#include "BuffType.h"
class FlashSkill : public BuffType
{
public:
    FlashSkill(Player* owner);
    virtual ~FlashSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void CastStop();

};

