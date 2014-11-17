#pragma once
#include "Unit.h"
class Missile :	public Unit
{


public:
	Missile();
	Missile::Missile(int unitId, int missileId, b2Vec2 initPos, b2Vec2 targetPos);
	virtual~Missile();

	
	void			SetMissileDamage(int missileDamage) { m_Damage = missileDamage; }
	void			SetMissileSpeed(float missileSpeed) { m_Speed = missileSpeed; }
	void			SetMissileLivetime(float missileLivetime) { m_Livetime = missileLivetime; }



	virtual void	MissileShoot();
	virtual void	ConsumeLiveTime(float costTime);
	virtual void	BeginCrashed();
	virtual void	Crashing(bool isCrashing);

protected:
	int m_Damage;
	float m_Livetime;
};

