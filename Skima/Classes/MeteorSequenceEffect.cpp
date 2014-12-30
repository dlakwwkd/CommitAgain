#include "pch.h"
#include "MeteorSequenceEffect.h"
#include "ObjectLayer.h"

MeteorSequenceEffect::MeteorSequenceEffect(const Vec2& targetPos)
{
    m_MeteorParticle = ParticleSystemQuad::create("Images/Effect/meteorEtoW.plist");

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
     CreateSprite("Images/Unit/CloackingUnit.png", createPos, 1.5f,1.95f);
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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/FirePool/explode.plist");
}

void MeteorSequenceEffect::ShowExplodeSprite()
{
    m_Sprite->runAction(MakeFastAnimationOnce("explode%02d.png", 15));
}

void MeteorSequenceEffect::SetParticleVisible(ParticleSystemQuad* particle)
{
    particle->setVisible(true);
}

Size MeteorSequenceEffect::GenerateInitPos(const Vec2&targetpos)
{
    auto winSize = Director::getInstance()->getWinSize();

    if (targetpos.x < winSize.width * 1 / 16)
    {
        return Size(0, winSize.height) ;
    }
    else if (winSize.width * 1 / 16 <= targetpos.x && targetpos.x < winSize.width * 3 / 16)
    {
        return Size(winSize.width * 2 / 16, winSize.height);
    }
    else if (winSize.width * 3 / 12 <= targetpos.x && targetpos.x < winSize.width * 5 / 16)
    {
        return Size(winSize.width * 4 / 16, winSize.height);
    }
    else if (winSize.width * 5 / 16 <= targetpos.x && targetpos.x < winSize.width * 7 / 16)
    {
        return Size(winSize.width * 6 / 16, winSize.height);
    }
    else if (winSize.width * 7 / 16 <= targetpos.x && targetpos.x < winSize.width * 9 / 16)
    {
        return Size(winSize.width * 8 / 16, winSize.height);
    }
    else if (winSize.width * 9 / 16 <= targetpos.x && targetpos.x < winSize.width * 11 / 16)
    {
        return Size(winSize.width * 10 / 16, winSize.height);
    }
    else if (winSize.width * 11 / 16 <= targetpos.x && targetpos.x < winSize.width * 13 / 16)
    {
        return Size(winSize.width * 12 / 16, winSize.height);
    }
    else if (winSize.width * 13 / 16 <= targetpos.x && targetpos.x < winSize.width * 15 / 16)
    {
        return Size(winSize.width * 14 / 16, winSize.height);
    }
    else
    {
        return Size(winSize.width,winSize.height);
    }
}

