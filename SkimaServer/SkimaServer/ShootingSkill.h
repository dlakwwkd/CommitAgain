#pragma once
#include "Skill.h"
#include "Missile.h"

class ShootingSkill : public Skill
{
public:
	ShootingSkill();
	ShootingSkill(int playerid);
	virtual ~ShootingSkill();
	
	b2Vec2 GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos);
	int MakeMissileUnitId(int playerId);
	virtual void ShootSkill(int unitId, b2Vec2 initPos, b2Vec2 targetPos);
	
protected:	
	


protected:
	float	m_MissileSpeed;
	float	m_MissileLiveTime;
	

};

