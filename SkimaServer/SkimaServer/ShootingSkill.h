#pragma once
#include "Skill.h"
#include "Missile.h"

class ShootingSkill : public Skill
{
public:
	ShootingSkill();
	ShootingSkill(int playerid);
	virtual ~ShootingSkill();
	
	virtual void ShootSkill(int unitId, b2Vec2 targetPos);

protected:	
	


protected:
	float	m_MissileSpeed;
	float	m_MissileLiveTime;
	

};

