#pragma once
#include "Missile.h"
class IceballMissile :
	public Missile
{
public:
	IceballMissile();
	IceballMissile::IceballMissile(int playerId, int unitId, b2Vec2 heroPos, b2Vec2 targetPos);
	virtual~IceballMissile();
};

