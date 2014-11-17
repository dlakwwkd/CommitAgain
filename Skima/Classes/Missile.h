#pragma once
#include "Unit.h"
class Missile :
	public Unit
{
public:
	Missile();
	~Missile();

public:
	virtual void MissileCast(Point createPos, Point targetPos, int missileID) = 0;

protected:
	int m_MissileID;

};

