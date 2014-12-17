#pragma once
#include "UnitPool.h"
class Missile : public UnitPool
{
public:
    Missile(int unitId);
    virtual ~Missile();
    virtual void	Extinction();
    void	        MissileShoot();
};

