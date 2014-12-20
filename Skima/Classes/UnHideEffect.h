#pragma once
#include "EffectSpriteType.h"
class UnHideEffect : public EffectSpriteType
{
public:
    UnHideEffect();
    virtual ~UnHideEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void	ExtinctEffect();

};
