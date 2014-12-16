#pragma once
#include "EffectParticleType.h"
class TeleportEffect : public EffectParticleType
{
public:
    TeleportEffect();
    virtual ~TeleportEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void	ExtinctEffect();

};
