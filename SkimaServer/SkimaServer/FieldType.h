#pragma once
#include "Skill.h"
class FieldType : public Skill
{
public:
    FieldType();
    virtual ~FieldType();

    virtual void    SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos) = 0;
protected:
    void            FieldDamage(b2Vec2 targetPos, float scale, int damage);
    void            FieldDamageRepeat(b2Vec2 targetPos, float scale, int damage, int repeatNum, int repeatDelay);

protected:
    float           m_Scale;
};

