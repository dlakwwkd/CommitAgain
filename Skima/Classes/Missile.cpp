#include "pch.h"
#include "Missile.h"
#include "GameManager.h"
#include "ObjectLayer.h"
#include "Effect.h"


Missile::Missile(int unitId)
{
    m_UnitID = SET_MAIN_TYPE(unitId, UNIT_MISSILE);
	m_InUse = false;
}


Missile::~Missile()
{
}

void Missile::MissileCast(const char* image, float speed, Vec2 createPos, Vec2 targetPos)
{
    m_Particle = ParticleSystemQuad::create(image);
	m_Particle->setPosition(createPos);
	m_Particle->setScale(0.65f);
	auto distance = createPos.distance(targetPos);
    auto time = distance / speed;
	auto action1 = MoveTo::create(time, targetPos);
	auto action2 = DelayTime::create(1.0f);
	auto action3 = CallFunc::create(CC_CALLBACK_0(Missile::MissileDelete, this));
	auto action4 = Sequence::create(action1, action2, action3, NULL);
	m_Particle->runAction(action4);
	GET_OBJECT_LAYER->addChild(m_Particle, 19);
}

void Missile::MissileCrash()
{
    if (m_Particle == nullptr) return;
	m_Particle->stopAllActions();

	auto action1 = DelayTime::create(1.0f);
	auto action2 = CallFunc::create(CC_CALLBACK_0(Missile::MissileDelete, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Particle->runAction(action3);

    auto type = GET_SIDE_TYPE(m_UnitID);
    switch (type)
    {
    case MS_FIRE_BALL:  type = EF_FIRE; break;
    case MS_ICE_BALL:   type = EF_ICE;  break;
    default: return;
    }
	auto effect = GET_EM->Assign(EffectType(type));
	effect->CreateEffect(m_Particle->getPosition());
}

void Missile::MissileDelete()
{
    if (m_Particle == nullptr) return;
    m_Particle->stopAllActions();
	GET_OBJECT_LAYER->removeChild(m_Particle);
	GET_OBJECT_LAYER->DeleteMissile(m_UnitID);
    m_Particle = nullptr;
}
