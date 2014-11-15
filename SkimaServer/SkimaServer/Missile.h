#pragma once
#include "Unit.h"
class Missile :	public Unit
{


public:
	Missile();
	Missile::Missile(int playerId, b2Vec2 pos);
	~Missile();

	virtual void MissileShoot(b2Vec2 currentPos, b2Vec2 targetPos);
};

