#pragma once
#include "FieldType.h"
class FireWallSkill : public FieldType
{
public:
    FireWallSkill(Player* owner);
    virtual ~FireWallSkill();

    virtual void    SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void    CastStop(){}

    b2Vec2          GenerateNextCenterPos(WallDirection direction);
    void            DoNextAttack();

private:
    int             m_CallCount;
    b2Vec2          m_PrevTaretPos;
};

