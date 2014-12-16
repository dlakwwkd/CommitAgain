#pragma once
#include "EffectParticleType.h"
class FireEffect : public EffectParticleType
{
public:
    FireEffect();
    virtual ~FireEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void	ExtinctEffect();

};

