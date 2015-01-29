#pragma once
#include "Unit.h"
class Missile :	public Unit
{
public:
    Missile(int unitId);
    virtual ~Missile();

public:
    void MissileCast(const char* image, const char* soundEffect, float speed, Vec2 createPos, Vec2 targetPos);
    void MissileCrash();
    void MissileDelete();

private:
    virtual void SetMoveMotionByDir(){}
    virtual void SetMoveMotionToCache(){}

protected:
    ParticleSystemQuad* m_Particle = nullptr;
};

