#pragma once
#include "EffectSpriteType.h"
#include "Enums.h"
class SwipeEffect : public EffectSpriteType
{
public:
    SwipeEffect();
    virtual ~SwipeEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();

    void            SetSwipeMotionCache();
    void            ShowSwipeMotionByDir(Direction dir);
};

