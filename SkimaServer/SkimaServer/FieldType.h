#pragma once
#include "Skill.h"
class FieldType : public Skill
{
public:
    FieldType();
    virtual ~FieldType();

    virtual void	SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos) = 0;
protected:
    void			FieldDamage(const b2Vec2& targetPos, float scale, int damage);
    void            FieldDamageRepeat(b2Vec2 targetPos, float scale, int damage, int repeatNum, int repeatDelay);
    void            FieldDamageInfinite(b2Vec2 targetPos, float scale, int damage, float repeatDelay);

protected:
    float           m_Scale;
};

