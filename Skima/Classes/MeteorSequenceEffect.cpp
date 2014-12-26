#include "pch.h"
#include "MeteorSequenceEffect.h"
#include "ObjectLayer.h"

MeteorSequenceEffect::MeteorSequenceEffect(const Vec2& targetPos)
{
    auto winSize = Director::getInstance()->getWinSize();

    m_MeteorParticle = ParticleSystemQuad::create("Laphinx/meteorEtoW.plist");
    m_MeteorParticle->setPosition(winSize.width-50.0f,winSize.height);
    m_MeteorParticle->setScale(0.8f);
    m_MeteorParticle->setVisible(false);
    GET_OBJECT_LAYER->addChild(m_MeteorParticle, 20);

    auto action1 = DelayTime::create(1.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(MeteorSequenceEffect::SetParticleVisible, this,m_MeteorParticle));
    auto action3 = MoveTo::create(0.2f,targetPos);
    auto action4 = CallFunc::create(CC_CALLBACK_0(MeteorSequenceEffect::ExtinctMeteorParticle, this));
    auto action5 = CallFunc::create(CC_CALLBACK_0(MeteorSequenceEffect::ShowExplodeSprite, this));
    auto action6 = Sequence::create(action1, action2,action3,action4,action5, NULL);
    m_MeteorParticle->runAction(action6);
}

MeteorSequenceEffect::~MeteorSequenceEffect()
{
}

void MeteorSequenceEffect::CreateEffect(const Vec2& createPos)
{
     CreateSprite("Images/CloackingUnit.png", createPos, 3.0f,1.4f);
     SetExplodeCache();
}

void MeteorSequenceEffect::ExtinctEffect()
{
    ExtinctSprite();
}

void MeteorSequenceEffect::ExtinctMeteorParticle()
{
    GET_OBJECT_LAYER->removeChild(m_MeteorParticle);
}

void MeteorSequenceEffect::SetExplodeCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/FirePool/explode.plist");
}

void MeteorSequenceEffect::ShowExplodeSprite()
{
    m_Sprite->runAction(MakeAnimationOnce("explode%02d.png", 15));
}

void MeteorSequenceEffect::SetParticleVisible(ParticleSystemQuad* particle)
{
    particle->setVisible(true);
}

