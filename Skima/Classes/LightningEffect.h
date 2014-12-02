#pragma once
#include "Effect.h"
class LightningEffect : public Effect
{
public:
    LightningEffect(int ID);
    ~LightningEffect();

    virtual void    CreateEffect(Vec2 createPos);
    virtual void    ExtinctEffect();

private:
    ParticleSystemQuad* m_Particle;
};

