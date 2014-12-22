#pragma once
#include "Skill.h"
class FieldType : public Skill
{
public:
    FieldType();
    virtual ~FieldType();

    virtual void	SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos) = 0;
    void            SetGameOn(bool gameOn) { m_GameOn = gameOn; }

protected:
    void			FieldDamage(const b2Vec2& targetPos, float scale, int damage);

protected:
    float           m_Scale;
    bool            m_GameOn = true;
};

