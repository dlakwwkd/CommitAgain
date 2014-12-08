#pragma once

USING_NS_CC;

class Effect
{
public:
    Effect();
    virtual ~Effect();

    virtual void CreateEffect(Vec2 createPos) = 0;
    virtual void ExtinctEffect() = 0;

protected:
    ParticleSystemQuad* m_Particle;
};

