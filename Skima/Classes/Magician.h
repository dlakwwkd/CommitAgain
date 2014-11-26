#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
	Magician(Point createPos, float scale);
	virtual ~Magician();

public:
	void SetMoveMotionByDir();

private:
	//ParticleSystemQuad* m_TeleportParticle;

};

