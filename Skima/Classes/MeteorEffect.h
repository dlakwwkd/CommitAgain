#pragma once
#include "EffectSpriteType.h"
#include "EffectParticleType.h"
#include "Enums.h"

class MeteorEffect : public EffectSpriteType
{
public:
    MeteorEffect();
    virtual ~MeteorEffect();

    virtual void    	CreateEffect(const Vec2& createPos);
    virtual void        ExtinctEffect();

    void                SetExplodeCache();
    void                ShowExplodeSprite();
    void                ExtinctMeteorParticle();
    void                SetParticleVisible(ParticleSystemQuad* particle);
    void                MakeExplodeSound();
    Size                GenerateInitPos(const Vec2&targetpos);
    

protected:
    ParticleSystemQuad* m_MeteorParticle;

};

