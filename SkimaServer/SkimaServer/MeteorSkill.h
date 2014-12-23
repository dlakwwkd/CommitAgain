#pragma once
#include "FieldType.h"
class MeteorSkill : public FieldType
{
public:
    MeteorSkill(Player* owner);
    virtual ~MeteorSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void CastStop(){}
};

