#include "pch.h"
#include "LightningPumpkinEffect.h"
#include "ObjectLayer.h"
#include "Macros.h"


LightningPumpkinEffect::LightningPumpkinEffect()
{
}


LightningPumpkinEffect::~LightningPumpkinEffect()
{
}

void LightningPumpkinEffect::CreateEffect(Vec2 createPos)
{
    m_Particle = ParticleSystemQuad::create("Jupiter/LightningPumpkin.plist");
    m_Particle->setPosition(createPos);
    m_Particle->setScale(0.4f);
    auto action1 = DelayTime::create(2.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(LightningPumpkinEffect::ExtinctEffect, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Particle->runAction(action3);
    GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void LightningPumpkinEffect::ExtinctEffect()
{
    GET_OBJECT_LAYER->removeChild(m_Particle);
    delete this;
}
