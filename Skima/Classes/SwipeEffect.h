#pragma once
#include "Effect.h"
#include "Enums.h"

class SwipeEffect : public Effect
{
public:
    SwipeEffect();
    ~SwipeEffect();

    Animate*        MakeAnimationOnce(const char* format, int size);
    virtual void    CreateEffect(Vec2 createPos);
    virtual void    ExtinctEffect();
    void            SetSwipeMotionCache();
    void            ShowSwipeMotionByDir(Direction dir);

private:
    Sprite*         m_RealSprite;
};

