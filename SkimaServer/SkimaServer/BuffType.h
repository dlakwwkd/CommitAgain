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
    void			DashSkillCast();
    void            DashSkillEnd();
    void            HideSkillCast();
    void            HideSkillEnd();

    void            MoveSpeedBonus(int duration, float bonus);
    void            MoveSpeedBonusEnd(float bonus);
    void            DamageUpBonus(int duration, int bonus);
    void            DamageUpBonusEnd(int bonus);
    void            ShieldBonus(int bonus);
    void            ShieldBonusEnd();
    void            HpBonus(int bonus);
    void            DamageBonus(int duration, int bonus);
    void            DamageBonusEnd(int bonus);
    void            CooltimeBonus(int duration, float bonus);
    void            CooltimeBonumEnd(float bonus);

protected:
    int             m_Duration;
    float           m_SpeedBonus;
};

