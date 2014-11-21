#pragma once
#include "Unit.h"
class Missile :	public Unit
{


public:
	Missile();
	virtual ~Missile();

	void	SetMissileInit(int playerId, b2Vec2 initPos);
	void	SetMissileTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	void	SetMissileDamage(int missileDamage) { m_Damage = missileDamage; }
	void	SetMissileSpeed(float missileSpeed) { m_Speed = missileSpeed; }
	void	SetMissileLivetime(float missileLivetime) { m_Livetime = missileLivetime; }
	void	SetMissileRange(float missileRange) { m_Range = missileRange; }

	void	MissileShoot();
	void	ConsumeLiveTime(float costTime);

protected:
	int		m_Damage;
	float   m_Range;
	float	m_Livetime;
};

