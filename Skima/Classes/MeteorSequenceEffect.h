#pragma once
#include "EffectSpriteType.h"
#include "EffectParticleType.h"
#include "Enums.h"
class MeteorSequenceEffect : public EffectSpriteType
{
public:
    MeteorSequenceEffect(const Vec2& targetPos);
    virtual ~MeteorSequenceEffect();

    virtual void    	CreateEffect(const Vec2& createPos);
    virtual void        ExtinctEffect();

    void                SetExplodeCache();
    void                ShowExplodeSprite();
    void                ExtinctMeteorParticle();
    void                SetParticleVisible(ParticleSystemQuad* particle);
protected:
    ParticleSystemQuad* m_MeteorParticle;

};

