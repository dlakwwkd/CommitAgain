#pragma once
#include "Unit.h"
class Missile :	public Unit
{


public:
	Missile();
	Missile::Missile(int playerId, int unitId, b2Vec2 initPos, b2Vec2 targetPos);
	virtual~Missile();

	virtual	void SetMissileDamage(int missileDamage) { m_Damage = missileDamage; }
	virtual void SetMissileSpeed(float missileSpeed) { m_Speed = missileSpeed; }
	virtual void SetMissileLivetime(float missileLivetime) { m_Livetime = missileLivetime; }

	virtual void MissileShoot();
	virtual void ConsumeLiveTime(float costTime);

protected:
	int m_Damage;
	float m_Livetime;
};

