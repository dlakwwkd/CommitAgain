#pragma once
#include "EffectParticleType.h"
class MeteorEffect : public EffectParticleType
{
public:
    MeteorEffect();
    virtual ~MeteorEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();
};

