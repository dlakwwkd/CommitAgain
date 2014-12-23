#pragma once
#include "Skill.h"
class Missile;

class ShootType : public Skill
{
public:
    ShootType();
    virtual ~ShootType();
    
    virtual void	SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos) = 0;
    virtual void    CastStop(SkillKey key) = 0;
protected:
    b2Vec2			GenerateInitPos(const b2Vec2& heroPos, const b2Vec2& targetPos);
	void            ShootMissile(const b2Vec2& initPos);
	void            ShootMissile(const b2Vec2& initPos, const b2Vec2& targetPos, MissileType type, float speed, float range, int damage){}
    
protected:
    MissileType     m_MissileType;
    float           m_MissileSpeed;
    float           m_MissileScale;
    int             m_MissileHp;
};

