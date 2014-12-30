#include "pch.h"
#include "Missile.h"
#include "GameManager.h"
#include "ObjectLayer.h"
#include "FireEffect.h"
#include "IceEffect.h"
#include "SparkEffect.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Missile::Missile(int unitId)
{
    m_UnitType = UNIT_MISSILE;
    m_UnitID = unitId;
    m_InUse = false;
}


Missile::~Missile()
{
}

void Missile::MissileCast(const char* image, const char* soundEffect, float speed, Vec2 createPos, Vec2 targetPos)
{
    SimpleAudioEngine::getInstance()->playEffect(soundEffect);
    m_Particle = ParticleSystemQuad::create(image);
    m_Particle->setPosition(createPos);
    m_Particle->setScale(0.65f);
    auto distance = createPos.distance(targetPos);
    auto time = distance / speed;
    auto action1 = MoveTo::create(time, targetPos);
    auto action2 = DelayTime::create(1.0f);
    auto action3 = CallFunc::create(CC_CALLBACK_0(Missile::MissileDelete, this));
    auto action4 = Sequence::create(action1, action2, action3, NULL);
	GET_OBJECT_LAYER->addChild(m_Particle, 19);
    m_Particle->runAction(action4);
}

void Missile::MissileCrash()
{
    if (m_Particle == nullptr) return;
    m_Particle->stopAllActions();

    auto action1 = DelayTime::create(1.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(Missile::MissileDelete, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Particle->runAction(action3);

    Effect* effect;
    auto type = GET_SIDE_TYPE(m_UnitID);

    switch (type)
    {
	case MS_FIRE_BALL:  
        effect = new FireEffect();  break;
	case MS_ICE_BALL:   
        effect = new IceEffect();   break;
	case MS_SPARK:      
        effect = new SparkEffect(); break;
	default: return;
    }
    effect->CreateEffect(m_Particle->getPosition());
}

void Missile::MissileDelete()
{
    if (m_Particle == nullptr) return;
    GET_OBJECT_LAYER->removeChild(m_Particle);
    m_Particle = nullptr;
    GET_OBJECT_LAYER->DeleteMissile(m_UnitID);
}

void Missile::SetMoveMotionToCache()
{

}

void Missile::SetMoveMotionByDir()
{

}
