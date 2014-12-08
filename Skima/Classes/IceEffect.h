#pragma once
#include "Effect.h"
class IceEffect : public Effect
{
public:
    IceEffect();
    virtual ~IceEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();

};

