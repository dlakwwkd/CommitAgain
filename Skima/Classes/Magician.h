#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
	Magician(Vec2 createPos, float scale);
	virtual ~Magician();

public:
	void SetMoveMotionByDir();

private:
	//ParticleSystemQuad* m_TeleportParticle;

};

