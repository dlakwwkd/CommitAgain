﻿#pragma once
#include "Missile.h"


class FireballMissile :	public Missile
{
public:
	FireballMissile(int unitId);
	virtual ~FireballMissile();

public:
	virtual void MissileCast(Point createPos, Point targetPos);
	virtual void MissileCrash();
	void MissileDelete();
	
private:
	ParticleSystemQuad* m_Particle;
};

