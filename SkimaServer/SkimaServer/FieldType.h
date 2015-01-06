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
    b2Vec2          GenerateNextCenterPos(Direction dir, float var);
    void			FieldDamage(const b2Vec2& targetPos, float scale, int damage);

protected:
    float           m_Scale;
    int             m_CallCount;
    b2Vec2          m_TaretPos;
};

