#include "pch.h"
#include "LightningEffect.h"
#include "TcpClient.h"
#include "ObjectLayer.h"
#include "GameManager.h"

LightningEffect::LightningEffect(int ID)
{
    m_EffectType = EF_LIGHTNING;
    m_ID = ID;
}


LightningEffect::~LightningEffect()
{
}

void LightningEffect::CreateEffect(Vec2 createPos)
{
    m_Particle = ParticleSystemQuad::create("Jupiter/lightning_effect.plist");
    auto particle2 = ParticleSystemQuad::create("Jupiter/lightning.plist");
    auto particle3 = ParticleSystemQuad::create("Jupiter/lightning_cloud.plist");
    particle2->setAnchorPoint(Vec2(0.50f, 0.0f));
    m_Particle->setPosition(createPos);
    particle2->setPosition(Vec2(0, 190.0f));
    particle3->setPosition(Vec2(0, 400.0f));
    m_Particle->setScale(0.70f);
    particle2->setScale(0.70f);
    particle3->setScale(0.90f);
    m_Particle->addChild(particle2);
    m_Particle->addChild(particle3);

    auto action1 = DelayTime::create(1.0f);
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