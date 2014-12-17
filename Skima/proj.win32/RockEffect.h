#pragma once
#include "EffectParticleType.h"
class RockEffect : public EffectParticleType
{
public:
    RockEffect();
    virtual ~RockEffect();

    void CreateEffect(const Vec2& createPos);
    void ExtinctEffect();
};

