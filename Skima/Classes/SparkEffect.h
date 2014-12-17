#pragma once
#include "EffectParticleType.h"
class SparkEffect : public EffectParticleType
{
public:
    SparkEffect();
    virtual ~SparkEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void	ExtinctEffect();

};

