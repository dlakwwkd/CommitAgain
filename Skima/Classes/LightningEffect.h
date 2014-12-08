#pragma once
#include "Effect.h"
class LightningEffect : public Effect
{
public:
    LightningEffect();
    ~LightningEffect();

    virtual void    CreateEffect(Vec2 createPos);
    virtual void    ExtinctEffect();
};

