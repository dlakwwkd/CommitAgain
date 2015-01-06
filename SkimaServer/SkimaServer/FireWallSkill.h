#pragma once
#include "FieldType.h"
class FireWallSkill : public FieldType
{
public:
    FireWallSkill(Player* owner);
    virtual ~FireWallSkill();

    virtual void    SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void    CastStop(){}

    void            DiagonalRadiation();
    void            CrossRadiation();
};

