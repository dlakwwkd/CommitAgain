#include "pch.h"
#include "IceballMissile.h"
#include "TcpClient.h"
#include "ObjectLayer.h"
#include "GameManager.h"
#include "Effect.h"


IceballMissile::IceballMissile(int unitId)
{
	m_MissileType = MS_ICE_BALL;
	m_UnitID = unitId;
	m_Speed = 800.0f;
}


IceballMissile::~IceballMissile()
{
}

void IceballMissile::MissileCast(Vec2 createPos, Vec2 targetPos)
{
	m_Particle = ParticleSystemQuad::create("Images/ice.plist");
	m_Particle->setPosition(createPos);
	m_Particle->setScale(0.60f);
    auto distance = createPos.distance(targetPos);
    auto time = distance / m_Speed;
    auto action1 = MoveTo::create(time, targetPos);
	auto action2 = DelayTime::create(1.0f);
	auto action3 = CallFunc::create(CC_CALLBACK_0(IceballMissile::MissileDelete, this));
	auto action4 = Sequence::create(action1, action2, action3, NULL);
	m_Particle->runAction(action4);
	GET_OBJECT_LAYER->addChild(m_Particle, 19);
}

void IceballMissile::MissileCrash()
{
	m_Particle->stopAllActions();

	auto action1 = DelayTime::create(1.0f);
	auto action2 = CallFunc::create(CC_CALLBACK_0(IceballMissile::MissileDelete, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Particle->runAction(action3);

	auto effect = GET_EM->Assign(EF_ICE);
	effect->CreateEffect(m_Particle->getPosition());
}

void IceballMissile::MissileDelete()
{
	GET_OBJECT_LAYER->removeChild(m_Particle);
	GET_OBJECT_LAYER->DeleteMissile(m_UnitID);
}
