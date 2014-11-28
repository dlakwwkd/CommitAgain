#pragma once
#include "Missile.h"
class IceballMissile : public Missile
{
public:
	IceballMissile(int unitId);
	virtual ~IceballMissile();

public:
	virtual void MissileCast(Vec2 createPos, Vec2 targetPos);
	virtual void MissileCrash();
	virtual void MissileDelete();
	
private:
	ParticleSystemQuad* m_Particle;
};

