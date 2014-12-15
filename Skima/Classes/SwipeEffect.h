#pragma once
#include "Effect.h"
class SwipeEffect : public Effect
{
public:
    SwipeEffect();
    ~SwipeEffect();

    virtual void    CreateEffect(Vec2 createPos);
    virtual void    ExtinctEffect();
};

