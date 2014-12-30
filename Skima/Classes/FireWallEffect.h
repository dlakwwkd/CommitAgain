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
    ParticleSystemQuad* m_FireParticle;
};

