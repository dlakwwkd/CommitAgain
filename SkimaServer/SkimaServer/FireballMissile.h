#pragma once
#include "Missile.h"
class FireballMissile : public Missile
{
public:
	FireballMissile();
	FireballMissile(int playerId, int unitId, b2Vec2 heroPos, b2Vec2 targetPos);

	virtual~FireballMissile();
};

