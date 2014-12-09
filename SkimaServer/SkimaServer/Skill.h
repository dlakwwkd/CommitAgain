#pragma once
#include "../../PacketType.h"
class Player;

class Skill
{
public:
    Skill();
    virtual ~Skill();

    int GetSkillDamage() { return m_Damage; }

    virtual void SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos) = 0;

protected:
    Player* m_Owner;
    int     m_Damage;
    float   m_Range;
    float   m_HeroBodySize;
};

