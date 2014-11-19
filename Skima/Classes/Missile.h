#pragma once
#include "Unit.h"
class Missile :
	public Unit
{
public:
	Missile();
	~Missile();

public:
	virtual void MissileCast(Point createPos, Point targetPos) = 0;
	virtual void MissileCrash() = 0;
};

