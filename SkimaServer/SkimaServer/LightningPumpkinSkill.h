#pragma once
#include "FieldType.h"
class LightningPumpkinSkill : public FieldType
{
public:
    LightningPumpkinSkill(Player* owner);
    virtual ~LightningPumpkinSkill();

    virtual void    SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos);
    virtual void    CastStop(){}

    WallDirection   GenerateDirection();
    b2Vec2          GenerateNextPos(WallDirection direction);
    float           GenerateFloatRandom(float num);
    void            DoNextAttack();

private:
    int             m_CallCount;
    b2Vec2          m_PrevTaretPos;
};
