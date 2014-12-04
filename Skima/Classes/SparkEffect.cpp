#include "pch.h"
#include "SparkEffect.h"
#include "TcpClient.h"
#include "ObjectLayer.h"
#include "GameManager.h"

SparkEffect::SparkEffect(int ID)
{
    m_EffectType = EF_SPARK;
    m_ID = ID;
}


SparkEffect::~SparkEffect()
{
}

void SparkEffect::CreateEffect(Vec2 createPos)
{
    m_Particle = ParticleSystemQuad::create("Jupiter/spark_effect.plist");
    m_Particle->setPosition(createPos);
    m_Particle->setScale(0.50f);
    auto action1 = DelayTime::create(2.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(SparkEffect::ExtinctEffect, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Particle->runAction(action3);
    GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void SparkEffect::ExtinctEffect()
{
    GET_OBJECT_LAYER->removeChild(m_Particle);
    GET_EM->Release(this);
}
