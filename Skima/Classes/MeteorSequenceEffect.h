#pragma once
#include "EffectSpriteType.h"
#include "Enums.h"
class MeteorSequenceEffect : public EffectSpriteType
{
public:
    MeteorSequenceEffect();
    virtual ~MeteorSequenceEffect();

    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();

    void            SetSwipeMotionCache();
    void            ShowSwipeMotionByDir(Direction dir);
};

