#pragma once
#include "BuffType.h"
class BuffSkill : public BuffType
{
public:
    BuffSkill(Player* owner);
    virtual ~BuffSkill();

    virtual void    SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos){}
    virtual void    CastStop(){}

    bool            IsShieldOn(){ return m_ShieldOn; }

    void            SpeedBuff();
    void            ShieldBuff();
    void            ShieldDestroy();
    void            HpBuff();
    void            DamageBuff();

protected:
    bool            m_ShieldOn = false;
};

