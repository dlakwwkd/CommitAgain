#pragma once
#include "PacketType.h"
class Hero;

USING_NS_CC;

class Skill
{
public:
    Skill();
    virtual ~Skill();

    int             GetCoolTime() { return m_CoolTime; }
    bool            GetCanUse() { return m_CanUse; }
    void            SetCanUse(bool isUse) { m_CanUse = isUse; }

    virtual void	SkillCast(Vec2 heroPos, Vec2 targetPos) = 0;
    virtual void    SkillReady() = 0;
    virtual void    SkillEnd() = 0;

protected:
    Hero*       m_Hero;
    int         m_CoolTime;
    bool        m_CanUse;
};

