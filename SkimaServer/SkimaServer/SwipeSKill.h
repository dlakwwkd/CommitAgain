#pragma once
#include "FieldType.h"
class SwipeSkill : public FieldType
{
public:
    SwipeSkill(Player* owner);
    virtual ~SwipeSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
};

