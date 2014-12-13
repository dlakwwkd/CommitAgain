#pragma once
#include "Skill.h"
class Missile;

class ShootType : public Skill
{
public:
    ShootType();
    virtual ~ShootType();
    
    virtual void    SkillCast(SkillKey key, b2Vec2 heroPos, b2Vec2 targetPos) = 0;
protected:
    b2Vec2          GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos);
    void            ShootMissile(b2Vec2 initPos);
    void            ShootMissile(b2Vec2 initPos, b2Vec2 targetPos, MissileType type, float speed, float range, int damage){}
    void            ShootMissileRepet(b2Vec2 initPos, int repeatNum, int repeatDelay);
    
protected:
    MissileType     m_MissileType;
    float           m_MissileSpeed;
    float           m_MissileScale;
    int             m_MissileHp;
};

