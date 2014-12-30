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
    void MissileExplosion();

private:
	float m_Range		= 0;
	float m_Livetime	= 0;

};

