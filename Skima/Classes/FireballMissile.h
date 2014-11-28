#pragma once
#include "Missile.h"
class FireballMissile :	public Missile
{
public:
	FireballMissile(int unitId);
	virtual ~FireballMissile();

public:
	virtual void MissileCast(Vec2 createPos, Vec2 targetPos);
	virtual void MissileCrash();
	virtual void MissileDelete();
	
private:
	ParticleSystemQuad* m_Particle;
};

