#pragma once
#include "Missile.h"
class FireballMissile :
	public Missile
{
public:
	FireballMissile(Point createPos, float scale);
	virtual ~FireballMissile();
};

