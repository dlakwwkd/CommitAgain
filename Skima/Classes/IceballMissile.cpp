﻿#include "pch.h"
#include "IceballMissile.h"
#include "TcpClient.h"
#include "ObjectLayer.h"


IceballMissile::IceballMissile(int unitId)
{
	m_MissileType = MS_ICE_BALL;
	m_UnitID = unitId;
}


IceballMissile::~IceballMissile()
{
}

void IceballMissile::MissileCast(Point createPos, Point targetPos)
{
	m_Particle = ParticleSystemQuad::create("Images/ice.plist");
	m_Particle->setPosition(createPos);
	auto distance = targetPos - createPos;
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 300;
	auto action1 = MoveTo::create(scala, targetPos);
	auto action2 = DelayTime::create(0.2f);
	auto action3 = CallFunc::create(CC_CALLBACK_0(IceballMissile::MissileDelete, this));
	auto action4 = Sequence::create(action1, action2, action3, NULL);
	m_Particle->runAction(action4);
	GET_OBJECT_LAYER->addChild(m_Particle);
}

void IceballMissile::MissileCrash()
{
	m_Particle->stopAllActions();

	auto action1 = DelayTime::create(0.2f);
	auto action2 = CallFunc::create(CC_CALLBACK_0(IceballMissile::MissileDelete, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Particle->runAction(action3);
}

void IceballMissile::MissileDelete()
{
	GET_OBJECT_LAYER->removeChild(m_Particle);
	GET_OBJECT_LAYER->DeleteMissile(m_UnitID);
}