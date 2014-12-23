#pragma once
#include "Effect.h"
class EffectParticleType : public Effect
{
public:
    EffectParticleType();
    virtual ~EffectParticleType();

    virtual void	CreateEffect(const Vec2& createPos) = 0;
    virtual void	ExtinctEffect() = 0;

protected:
    void			CreateParticle(const char* file, const Vec2& createPos, float scale, float lastTime);
    void			AddSubParticle(const char* file, const Vec2& anchorPoint, const Vec2& createPos, float scale);
    void			ExtinctParticle();
protected:
    ParticleSystemQuad* m_Particle = nullptr;
};

