#pragma once
#include "EffectParticleType.h"
class FireWallParticleEffect : public EffectParticleType
{
public:
    FireWallParticleEffect();
    virtual ~FireWallParticleEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void	ExtinctEffect();

};

