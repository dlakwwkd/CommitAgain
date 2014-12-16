#pragma once
#include "EffectParticleType.h"
class IceEffect : public EffectParticleType
{
public:
    IceEffect();
    virtual ~IceEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void	ExtinctEffect();

};

