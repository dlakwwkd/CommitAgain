#pragma once
#include "PacketType.h"
#include "EffectManager.h"
class Hero;

USING_NS_CC;

class Skill
{
public:
    Skill();
    Skill(Hero* hero);
    virtual ~Skill();

    int             GetCoolTime() { return m_CoolTime; }
    bool            GetCanUse() { return m_CanUse; }
    EffectType      GetEffectType(){ return m_EffectType; }
    SkillType       GetSkillType(){ return m_SkillType; }

    void            SetCanUse(bool isUse) { m_CanUse = isUse; }

    //virtual void	SkillCast(Vec2 heroPos, Vec2 targetPos, int missileID) = 0;
    virtual void    SkillReady() = 0;
    virtual void    SkillEnd() = 0;

protected:
    Hero*       m_Hero;

    SkillType   m_SkillType;
    EffectType  m_EffectType;
    int         m_CoolTime;
    bool        m_CanUse;
};

