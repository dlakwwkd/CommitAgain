#pragma once
#include "Skill.h"
#include "GameManager.h"
class FieldType : public Skill
{
public:
    FieldType();
    virtual ~FieldType();

    virtual void	SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos) = 0;
    virtual void    CastStop() = 0;

protected:
    void			FieldDamage(const b2Vec2& targetPos, float scale, int damage);
    void            WallFieldDamage(const b2Vec2& targetPos, WallDirection direction, int damage);
protected:
    float           m_Scale;
};

