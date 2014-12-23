#pragma once
#include "Skill.h"
class BuffType : public Skill
{
public:
    BuffType();
    virtual ~BuffType();

    virtual void	SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos) = 0;
    virtual void    CastStop() = 0;

protected:
    void			MoveSpeedBonus();
    void            MoveSpeedBonusEnd();

protected:
    int             m_Duration;
    float           m_SpeedBonus;
};

