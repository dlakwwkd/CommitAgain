#pragma once
#include "Unit.h"
class Missile :	public Unit
{


public:
	Missile();
	Missile::Missile(int unitId, int missileId, b2Vec2 initPos, b2Vec2 targetPos);
	virtual~Missile();

	void			SetMissileInit(int playerId, b2Vec2 initPos);
	void			SetMissileTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	void			SetMissileDamage(int missileDamage) { m_Damage = missileDamage; }
	void			SetMissileSpeed(float missileSpeed) { m_Speed = missileSpeed; }
	void			SetMissileLivetime(float missileLivetime) { m_Livetime = missileLivetime; }

// 
// 	void			BeginCrashed();
// 	void			Crashing(bool isCrashing);

	virtual void	MissileShoot();
	virtual void	ConsumeLiveTime(float costTime);

protected:
	int m_Damage;
	float m_Livetime;
};

