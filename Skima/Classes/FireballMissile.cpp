﻿#include "pch.h"
#include "FireballMissile.h"
#include "TcpClient.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "Effect.h"


FireballMissile::FireballMissile(int unitId)
{
	m_MissileType = MS_FIRE_BALL;
	m_UnitID = unitId;
	m_Speed = 1200.0f;
}


FireballMissile::~FireballMissile()
{
}

void FireballMissile::MissileCast(Vec2 createPos, Vec2 targetPos)
{
	m_Particle = ParticleSystemQuad::create("Images/fire.plist");
	m_Particle->setPosition(createPos);
	m_Particle->setScale(0.70f);
	auto distance = createPos.distance(targetPos);
	auto time = distance / m_Speed;
	auto action1 = MoveTo::create(time, targetPos);
	auto action2 = DelayTime::create(1.0f);
	auto action3 = CallFunc::create(CC_CALLBACK_0(FireballMissile::MissileDelete, this));
	auto action4 = Sequence::create(action1, action2, action3, NULL);
	m_Particle->runAction(action4);
	GET_OBJECT_LAYER->addChild(m_Particle, 19);
}

void FireballMissile::MissileCrash()
{
	m_Particle->stopAllActions();

	auto action1 = DelayTime::create(1.0f);
	auto action2 = CallFunc::create(CC_CALLBACK_0(FireballMissile::MissileDelete, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Particle->runAction(action3);

	auto effect = GET_EM->Assign(EF_FIRE);
	effect->CreateEffect(m_Particle->getPosition());
}

void FireballMissile::MissileDelete()
{
	m_Particle->stopAllActions();
	GET_OBJECT_LAYER->removeChild(m_Particle);
	GET_OBJECT_LAYER->DeleteMissile(m_UnitID);
}
