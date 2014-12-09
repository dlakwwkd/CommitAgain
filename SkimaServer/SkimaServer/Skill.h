﻿#pragma once
#include "../../PacketType.h"
#include "RefCountable.h"
class Player;

class Skill : public RefCountable
{
public:
    Skill();
    virtual ~Skill();

    int GetSkillDamage() { return m_Damage; }

    virtual void SkillCast(b2Vec2 heroPos, b2Vec2 targetPos) = 0;

protected:
    Player* m_Owner;
    b2Vec2  m_TargetPos;
    int     m_Damage;
    float   m_Range;
    float   m_HeroBodySize;
};

