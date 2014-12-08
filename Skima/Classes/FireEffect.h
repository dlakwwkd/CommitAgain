#pragma once
#include "Effect.h"
class FireEffect : public Effect
{
public:
    FireEffect();
    virtual ~FireEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();

};

