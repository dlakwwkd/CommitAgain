#include "pch.h"
#include "IceEffect.h"
#include "TcpClient.h"
#include "ObjectLayer.h"
#include "GameManager.h"


IceEffect::IceEffect(int ID)
{
	m_EffectType = EF_ICE;
	m_ID = ID;
}


IceEffect::~IceEffect()
{
}

void IceEffect::CreateEffect(Point createPos)
{
	m_Particle = ParticleSystemQuad::create("Images/ice_break.plist");
	m_Particle->setPosition(createPos);
	m_Particle->setScale(0.40f);
	auto action1 = DelayTime::create(2.0f);
	auto action2 = CallFunc::create(CC_CALLBACK_0(IceEffect::ExtinctEffect, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Particle->runAction(action3);
	GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void IceEffect::ExtinctEffect()
{
	GET_OBJECT_LAYER->removeChild(m_Particle);
	GET_EM->Release(this);
}
