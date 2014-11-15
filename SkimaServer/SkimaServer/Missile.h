#pragma once
#include "Unit.h"
class Missile :	public Unit
{


public:
	Missile();
	Missile::Missile(int playerId,int unitId);
	virtual~Missile();

	virtual void MissileShoot(b2Vec2 currentPos, b2Vec2 targetPos);
	virtual void ConsumeLiveTime(int costTime);
protected:
	int playerId;
};

