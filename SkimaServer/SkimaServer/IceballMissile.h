#pragma once
#include "Missile.h"
class IceballMissile :
	public Missile
{
public:
	IceballMissile();
	IceballMissile::IceballMissile(int playerId, b2Vec2 pos);
	~IceballMissile();
};

