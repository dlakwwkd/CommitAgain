#pragma once
#include "Effect.h"
class SparkEffect : public Effect
{
public:
    SparkEffect(int ID);
    virtual ~SparkEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();

private:
    ParticleSystemQuad* m_Particle;

};

