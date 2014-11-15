#pragma once
#include "Missile.h"
class IceballMissile :
	public Missile
{
public:
	IceballMissile();
	IceballMissile::IceballMissile(int playerId, int unitId);
	virtual~IceballMissile();
};

