#pragma once
#include "Unit.h"
#include "ObjectPool.h"
class Missile : public Unit, public ObjectPool<Missile>
{
public:
    Missile();
    virtual ~Missile();

	void SetRange(float range) { m_Range = range; }
	void SetLivetime(float livetime) { m_Livetime = livetime; }

	void MissileShoot();

private:
	float m_Range;
	float m_Livetime;

};

