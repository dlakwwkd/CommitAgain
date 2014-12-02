#pragma once
#include "Effect.h"
class IceEffect : public Effect
{
public:
    IceEffect(int ID);
    virtual ~IceEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();

private:
    ParticleSystemQuad* m_Particle;

};

