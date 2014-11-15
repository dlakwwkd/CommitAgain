#pragma once
#include "Missile.h"
class FireballMissile :
	public Missile
{
public:
	FireballMissile();
	FireballMissile(int playerId, int unitId);

	virtual~FireballMissile();
};

