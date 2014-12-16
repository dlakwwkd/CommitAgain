#pragma once
#include "EffectParticleType.h"
class LightningEffect : public EffectParticleType
{
public:
    LightningEffect();
    virtual ~LightningEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();
};

