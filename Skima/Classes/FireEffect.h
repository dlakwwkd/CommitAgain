#pragma once
#include "Effect.h"
class FireEffect : public Effect
{
public:
	FireEffect(int ID);
	virtual ~FireEffect();

	virtual void CreateEffect(Point createPos);
	virtual void ExtinctEffect();

private:
	ParticleSystemQuad* m_Particle;

};

