#pragma once
#include "EffectSpriteType.h"
#include "Enums.h"
class FireWallEffect : public EffectSpriteType
{
public:
    FireWallEffect();
    virtual ~FireWallEffect();

    void            CreateEffect(const Vec2& createPos, Direction direction);
    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();

    void            SetFireMotionCache();
    void            ShowFireMotionByDir(Direction dir);
};

