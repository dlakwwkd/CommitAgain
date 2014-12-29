#pragma once
#include "EffectSpriteType.h"
#include "Enums.h"
class FireWallEffect : public EffectSpriteType
{
public:
    FireWallEffect();
    virtual ~FireWallEffect();

    void            CreateFireEffect(Vec2 createPos);
    virtual void	CreateEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();

    void            SetFireMotionCache();
    void            ShowFireMotion();

public:
    Sprite*         m_FireSprite1;
    Sprite*         m_FireSprite2;
    Sprite*         m_FireSprite3;
    Sprite*         m_FireSprite4;
    Sprite*         m_FireSprite5;
    Sprite*         m_FireSprite6;
    Sprite*         m_FireSprite7;
    Sprite*         m_FireSprite8;

};

