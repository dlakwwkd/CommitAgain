#pragma once
#include "Unit.h"
#include "ObjectPool.h"
class Mob : public Unit, public ObjectPool<Mob>
{
public:
	Mob();
	virtual ~Mob();
};

