#pragma once
#include "Unit.h"
class Missile :	public Unit
{
public:
    Missile(int unitId);
    virtual ~Missile();

public:
    void MissileCast(const char* image, float speed, Vec2 createPos, Vec2 targetPos);
    void MissileCrash();
    void MissileDelete();

protected:
    ParticleSystemQuad* m_Particle;
};

