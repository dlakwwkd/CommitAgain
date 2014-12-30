#pragma once
#include "EffectSpriteType.h"
class LightningPumpkinEffect : public EffectSpriteType
{
public:
    LightningPumpkinEffect(const Vec2& targetPos);
    virtual ~LightningPumpkinEffect();

    virtual void    	CreateEffect(const Vec2& createPos);
    virtual void        ExtinctEffect();

    void                SetPumpkinCache();
    void                ShowPumpkinSprite();
    //void                ExtinctMeteorParticle();
    void                SetParticleVisible(ParticleSystemQuad* particle);
    Size                GenerateInitPos(const Vec2&targetpos);
};

