#pragma once
#include "EffectParticleType.h"
class RockEffect : public EffectParticleType
{
public:
    RockEffect();
    virtual ~RockEffect();

    void CreateEffect(Vec2 createPos);
    void ExtinctEffect();
};

