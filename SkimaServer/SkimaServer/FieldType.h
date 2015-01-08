#pragma once
#include "Skill.h"
enum Direction
{
    N,
    S,
    W,
    E,
    NW,
    NE,
    SW,
    SE,
};

class FieldType : public Skill
{
public:
    FieldType();
    virtual ~FieldType();

    virtual void	SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos) = 0;
    virtual void    CastStop() = 0;

protected:
    void			FieldDamage(const b2Vec2& targetPos, float scale, int damage);
    b2Vec2          GenerateNextCenterPos(Direction dir, float var);
    b2Vec2          GenerateRandomPos(float range);
    void            DiagonalRadiation(int delay, int repeatNum, int callNum);
    void            CrossRadiation(int delay, int repeatNum, int callNum);
    void            RandomAttack(float range, int delay, int repeatNum, int callNum);

protected:
    float           m_Scale;
    int             m_CallCount;
    b2Vec2          m_TaretPos;
};

