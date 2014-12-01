#pragma once
#include "Effect.h"
class TeleportEffect : public Effect
{
public:
    TeleportEffect(int ID);
    ~TeleportEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();

private:
    ParticleSystemQuad* m_Particle;

};
