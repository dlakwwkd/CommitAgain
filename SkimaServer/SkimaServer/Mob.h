#pragma once
#include "UnitPool.h"
class Mob : public UnitPool
{
public:
	Mob(int unitId);
	virtual ~Mob();
	virtual void	Extinction();
};

