#pragma once
#include "EffectParticleType.h"
class HideEffect : public EffectParticleType
{
public:
    HideEffect();
    virtual ~HideEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void	ExtinctEffect();

};
