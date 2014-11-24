#pragma once
#include "Unit.h"
class Missile :	public Unit
{
public:
	Missile();
	virtual ~Missile();

public:
	virtual void MissileCast(Point createPos, Point targetPos) = 0;
	virtual void MissileCrash() = 0;

protected:
	MissileType		m_MissileType;
	bool			m_InUse;

	friend class MissileManager;
};

