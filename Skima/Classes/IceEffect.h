#pragma once
#include "Effect.h"
class IceEffect : public Effect
{
public:
	IceEffect(int ID);
	virtual ~IceEffect();

	virtual void CreateEffect(Point createPos);
	virtual void ExtinctEffect();

private:
	ParticleSystemQuad* m_Particle;

};

