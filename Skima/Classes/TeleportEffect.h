#pragma once
#include "Effect.h"
class TeleportEffect : public Effect
{
public:
    TeleportEffect();
    ~TeleportEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();

};
