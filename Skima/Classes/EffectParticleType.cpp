#include "pch.h"
#include "EffectParticleType.h"
#include "EffectSpriteType.h"
#include "ObjectLayer.h"
#include "Macros.h"


EffectParticleType::EffectParticleType()
{
}


EffectParticleType::~EffectParticleType()
{
}

void EffectParticleType::CreateParticle(const char* file, const Vec2& createPos, float scale, float lastTime)
{
    m_Particle = ParticleSystemQuad::create(file);
    m_Particle->setPosition(createPos);
    m_Particle->setScale(scale);
    auto action1 = DelayTime::create(lastTime);
    auto action2 = CallFunc::create(CC_CALLBACK_0(EffectParticleType::ExtinctParticle, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Particle->runAction(action3);
    GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void EffectParticleType::AddSubParticle(const char* file, const Vec2& anchorPoint, const Vec2& createPos, float scale)
{
    auto particle = ParticleSystemQuad::create(file);
    particle->setAnchorPoint(anchorPoint);
    particle->setPosition(createPos);
    particle->setScale(scale);
    m_Particle->addChild(particle);
}

void EffectParticleType::ExtinctParticle()
{
    GET_OBJECT_LAYER->removeChild(m_Particle);
    delete this;
}
