#pragma once
#include "EffectSpriteType.h"
#include "Enums.h"
class FireWallEffect : public EffectSpriteType
{
public:
    FireWallEffect();
    virtual ~FireWallEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();

    void            SetSwipeMotionCache();
    void            ShowSwipeMotionByDir(Direction dir);
};

