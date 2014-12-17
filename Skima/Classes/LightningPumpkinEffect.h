#pragma once
#include "EffectParticleType.h"
class LightningPumpkinEffect : public EffectParticleType
{
public:
    LightningPumpkinEffect();
    virtual ~LightningPumpkinEffect();

    virtual void CreateEffect(const Vec2& createPos);
    virtual void ExtinctEffect();
};

