#pragma once
#include "EffectSpriteType.h"
#include "Enums.h"
class MeteorAfterEffect : public EffectSpriteType
{
public:
    MeteorAfterEffect();
    virtual ~MeteorAfterEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();

    void            SetSwipeMotionCache();
    void            ShowSwipeMotionByDir(Direction dir);
};

