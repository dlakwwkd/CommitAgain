#include "pch.h"
#include "MeteorEffect.h"
#include "ObjectLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

MeteorEffect::MeteorEffect()
{
}

MeteorEffect::~MeteorEffect()
{
}

void MeteorEffect::CreateEffect(const Vec2& createPos)
{
     CreateSprite("Images/Unit/CloackingUnit.png", createPos, 2.0f,2.05f);
     SetExplodeCache();
     m_MeteorParticle = ParticleSystemQuad::create("Images/Effect/meteor.plist");

     auto initPos = GenerateInitPos(createPos);
     m_MeteorParticle->setPosition(initPos);
     m_MeteorParticle->setScale(0.8f);
     m_MeteorParticle->setVisible(false);
     GET_OBJECT_LAYER->addChild(m_MeteorParticle, 20);

     auto action1 = DelayTime::create(0.75f);
     auto action2 = CallFunc::create(CC_CALLBACK_0(MeteorEffect::SetParticleVisible, this, m_MeteorParticle));
     auto action3 = MoveTo::create(0.45f, createPos);
     auto action4 = CallFunc::create(CC_CALLBACK_0(MeteorEffect::ExtinctMeteorParticle, this));
     auto sound = CallFunc::create(CC_CALLBACK_0(MeteorEffect::MakeExplodeSound, this));
     auto action5 = CallFunc::create(CC_CALLBACK_0(MeteorEffect::ShowExplodeSprite, this));
     auto action6 = Sequence::create(action1, action2, action3, action4, sound, action5, NULL);
     m_MeteorParticle->runAction(action6);
}

void MeteorEffect::ExtinctEffect()
{
    ExtinctSprite();
}

void MeteorEffect::ExtinctMeteorParticle()
{
    GET_OBJECT_LAYER->removeChild(m_MeteorParticle);
}

void MeteorEffect::SetExplodeCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/FirePool/explode.plist");
}

void MeteorEffect::ShowExplodeSprite()
{
    m_Sprite->runAction(MakeAnimation("explode%02d.png", 15, 0.05f));
}

void MeteorEffect::SetParticleVisible(ParticleSystemQuad* particle)
{
    particle->setVisible(true);
}

Size MeteorEffect::GenerateInitPos(const Vec2&targetpos)
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

void MeteorEffect::MakeExplodeSound()
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/explode.mp3");
}

