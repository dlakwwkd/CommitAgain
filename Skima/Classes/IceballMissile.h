#pragma once
#include "Missile.h"


class IceballMissile : public Missile
{
public:
	IceballMissile(int unitId);
	virtual ~IceballMissile();

public:
	virtual void MissileCast(Point createPos, Point targetPos);
	virtual void MissileCrash();
	void MissileDelete();
	
private:
	ParticleSystemQuad* m_Particle;
};

