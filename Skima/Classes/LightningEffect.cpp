#include "pch.h"
#include "LightningEffect.h"
#include "TcpClient.h"
#include "ObjectLayer.h"
#include "GameManager.h"

LightningEffect::LightningEffect(int ID)
{
    m_EffectType = EF_FIRE;
    m_ID = ID;
}


LightningEffect::~LightningEffect()
{
}

void LightningEffect::CreateEffect(Vec2 createPos)
{
    m_Particle = ParticleSystemQuad::create("Images/lightning_effect.plist");
    auto particle2 = ParticleSystemQuad::create("Images/lightning.plist");
    auto particle3 = ParticleSystemQuad::create("Images/lightning_cloud.plist");
    m_Particle->setPosition(createPos);
    m_Particle->setScale(0.50f);
    m_Particle->addChild(particle2);
    m_Particle->addChild(particle3);

    auto action1 = DelayTime::create(4.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(LightningEffect::ExtinctEffect, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Particle->runAction(action3);
    GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void LightningEffect::ExtinctEffect()
{
    GET_OBJECT_LAYER->removeChild(m_Particle);
    GET_EM->Release(this);
}