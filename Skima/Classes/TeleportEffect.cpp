#include "pch.h"
#include "TeleportEffect.h"
#include "TcpClient.h"
#include "ObjectLayer.h"
#include "GameManager.h"


TeleportEffect::TeleportEffect(int ID)
{
    m_EffectType = EF_TELE;
    m_ID = ID;
}


TeleportEffect::~TeleportEffect()
{
}

void TeleportEffect::CreateEffect(Vec2 createPos)
{
    m_Particle = ParticleSystemQuad::create("Images/PT_Teleport.plist");
    m_Particle->setPosition(createPos);
    m_Particle->setScale(0.40f);
    auto action1 = DelayTime::create(2.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(TeleportEffect::ExtinctEffect, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Particle->runAction(action3);
    GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void TeleportEffect::ExtinctEffect()
{
    GET_OBJECT_LAYER->removeChild(m_Particle);
    GET_EM->Release(this);
}