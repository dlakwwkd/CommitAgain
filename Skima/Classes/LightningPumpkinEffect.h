#pragma once
#include "Effect.h"
class LightningPumpkinEffect : public Effect
{
public:
    LightningPumpkinEffect();
    virtual ~LightningPumpkinEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();
};

