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

void FireballMissile::MissileCast(Point createPos, Point targetPos)
{
	m_Particle = ParticleSystemQuad::create("Images/fire.plist");
	m_Particle->setPosition(createPos);
	auto distance = targetPos - createPos;
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 300;
	auto action1 = MoveTo::create(scala, targetPos);
	auto action2 = DelayTime::create(0.2f);
	auto action3 = CallFunc::create(CC_CALLBACK_0(FireballMissile::MissileDelete, this));
	auto action4 = Sequence::create(action1, action2, action3, NULL);
	m_Particle->runAction(action4);
	GET_OBJECT_LAYER->addChild(m_Particle);
}

void FireballMissile::MissileCrash()
{
	m_Particle->stopAllActions();

	auto action1 = DelayTime::create(0.2f);
	auto action2 = CallFunc::create(CC_CALLBACK_0(FireballMissile::MissileDelete, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Particle->runAction(action3);
}

void FireballMissile::MissileDelete()
{
	GET_OBJECT_LAYER->removeChild(m_Particle);
	GET_OBJECT_LAYER->DeleteMissile(m_UnitID);
}
