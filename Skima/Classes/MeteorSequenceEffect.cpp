#include "pch.h"
#include "MeteorSequenceEffect.h"
#include "ObjectLayer.h"

MeteorSequenceEffect::MeteorSequenceEffect(const Vec2& targetPos)
{
    m_MeteorParticle = ParticleSystemQuad::create("Laphinx/meteorEtoW.plist");

    auto initPos = GenerateInitPos(targetPos);
    m_MeteorParticle->setPosition(initPos);
    m_MeteorParticle->setScale(1.0f);
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
     CreateSprite("Images/CloackingUnit.png", createPos, 1.5f,1.95f);
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
    m_Sprite->runAction(MakeFastAnimation("explode%02d.png", 15));
}

void MeteorSequenceEffect::SetParticleVisible(ParticleSystemQuad* particle)
{
    particle->setVisible(true);
}

Size MeteorSequenceEffect::GenerateInitPos(const Vec2&targetpos)
{
    auto winSize = Director::getInstance()->getWinSize();

    if (targetpos.x < winSize.width * 1 / 12)
    {
        return Size(0, winSize.height) ;
    }
    else if (winSize.width * 1 / 12 <= targetpos.x && targetpos.x < winSize.width * 3 / 12)
    {
        return Size(winSize.width*2/12, winSize.height);
    }
    else if (winSize.width * 3 / 12 <= targetpos.x && targetpos.x < winSize.width * 5 / 12)
    {
        return Size(winSize.width * 4 / 12, winSize.height);
    }
    else if (winSize.width * 5 / 12 <= targetpos.x && targetpos.x < winSize.width * 7 / 12)
    {
        return Size(winSize.width * 6 / 12, winSize.height);
    }
    else if (winSize.width * 7 / 12 <= targetpos.x && targetpos.x < winSize.width * 9 / 12)
    {
        return Size(winSize.width * 8 / 12, winSize.height);
    }
    else if (winSize.width * 9 / 12 <= targetpos.x && targetpos.x < winSize.width * 11 / 12)
    {
        return Size(winSize.width * 10 / 12, winSize.height);
    }
    else
    {
        return Size(winSize.width,winSize.height);
    }
}

