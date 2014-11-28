#pragma once
#include "Unit.h"
class Missile :	public Unit
{
public:
	Missile();
	virtual ~Missile();

public:
	virtual void MissileCast(Vec2 createPos, Vec2 targetPos) = 0;
	virtual void MissileCrash() = 0;
	virtual void MissileDelete() = 0;

protected:
	MissileType		m_MissileType;
	bool			m_InUse;

	friend class MissileManager;
};

