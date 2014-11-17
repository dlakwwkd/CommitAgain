#pragma once
#include "Missile.h"


class FireballMissile :
	public Missile
{
public:
	FireballMissile();
	~FireballMissile();

public:
	void MissileCast(Point createPos, Point targetPos);
	void MissileDelete();
	
private:
	ParticleSystemQuad* m_Particle;
};

