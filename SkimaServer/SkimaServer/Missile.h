#pragma once
#include "UnitPool.h"
class Missile : public UnitPool
{
public:
    Missile();
    virtual ~Missile();
    virtual void	Extinction();
    void	        MissileShoot();
};

