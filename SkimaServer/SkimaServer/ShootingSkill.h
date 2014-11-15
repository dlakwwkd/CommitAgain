#pragma once
#include "Skill.h"
class ShootingSkill :
	public Skill
{
public:
	ShootingSkill(int playerid);
	virtual ~ShootingSkill();

protected:
	virtual void Shoot(int unitId, b2Vec2 targetPos);

	int m_PlayerId;

	int	m_Speed;
	

};

