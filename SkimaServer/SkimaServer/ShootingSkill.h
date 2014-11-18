#pragma once
#include "Skill.h"
#include "Missile.h"

class ShootingSkill : public Skill
{
public:
	ShootingSkill();
	ShootingSkill(int playerid, float heroBodySize);
	~ShootingSkill();
	
	Missile*		 GetMissile(){ return m_Missile; }
	b2Vec2			 GenerateInitPos(b2Vec2 heroPos, b2Vec2 targetPos);
	void	 SkillCast(int unitId, b2Vec2 heroPos, b2Vec2 targetPos);
	
protected:	
	


protected:
	Missile* m_Missile;

	float	m_MissileSpeed;
	float	m_MissileLiveTime;
	

};

