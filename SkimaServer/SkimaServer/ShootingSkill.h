#pragma once
#include "Skill.h"
class Missile;

class ShootingSkill : public Skill
{
public:
	ShootingSkill();
	virtual ~ShootingSkill();
	
	b2Vec2			 GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos);

	virtual void	 SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos);
	
protected:
	float		m_MissileSpeed;
	float		m_MissileLiveTime;
	int			m_Hp;
};

