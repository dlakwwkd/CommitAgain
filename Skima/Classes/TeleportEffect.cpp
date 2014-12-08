#include "pch.h"
#include "TeleportEffect.h"
#include "ObjectLayer.h"
#include "Macros.h"


TeleportEffect::TeleportEffect()
{
}


TeleportEffect::~TeleportEffect()
{
}

void TeleportEffect::CreateEffect(Vec2 createPos)
{
    m_Particle = ParticleSystemQuad::create("Images/teleport.plist");
    m_Particle->setPosition(createPos);
    m_Particle->setScale(0.4f);
    auto action1 = DelayTime::create(2.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(TeleportEffect::ExtinctEffect, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Particle->runAction(action3);
    GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void TeleportEffect::ExtinctEffect()
{
    GET_OBJECT_LAYER->removeChild(m_Particle);
    delete this;
}