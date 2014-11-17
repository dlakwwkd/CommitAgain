#include "pch.h"
#include "FireballMissile.h"
#include "TcpClient.h"
#include "ObjectLayer.h"


FireballMissile::FireballMissile()
{
}


FireballMissile::~FireballMissile()
{
}

void FireballMissile::MissileCast(Point heroPos, Point targetPos)
{
	m_Particle = ParticleSystemQuad::create("Images/light.plist");
	m_Particle->setPosition(heroPos);
	auto distance = targetPos - heroPos;
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 300;
	auto action1 = MoveTo::create(scala, targetPos);
	auto action2 = CallFunc::create(CC_CALLBACK_0(FireballMissile::MissileDelete, this));
	auto action3 = Sequence::create(action1, 1.0f, action2, NULL);
	m_Particle->runAction(action3);
	GET_OBJECT_LAYER->addChild(m_Particle);
}

void FireballMissile::MissileDelete()
{
	GET_OBJECT_LAYER->removeChild(m_Particle);
}
