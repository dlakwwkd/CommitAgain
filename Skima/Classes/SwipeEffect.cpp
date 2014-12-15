#include "pch.h"
#include "SwipeEffect.h"
#include "ObjectLayer.h"
#include "Macros.h"

SwipeEffect::SwipeEffect()
{
    m_RealSprite = nullptr;
    SetSwipeMotionCache();
}


SwipeEffect::~SwipeEffect()
{
}

void SwipeEffect::CreateEffect(Vec2 createPos)
{
    //To do : sprite addchild ÇØÁÖ±â

//     m_Particle = ParticleSystemQuad::create("Jupiter/lightning_effect.plist");
//     auto particle2 = ParticleSystemQuad::create("Jupiter/lightning.plist");
//     auto particle3 = ParticleSystemQuad::create("Jupiter/lightning_cloud.plist");
//     particle2->setAnchorPoint(Vec2(0.50f, 0.0f));
//     m_Particle->setPosition(createPos);
//     particle2->setPosition(Vec2(0, 190.0f));
//     particle3->setPosition(Vec2(0, 400.0f));
//     m_Particle->setScale(0.70f);
//     particle2->setScale(0.70f);
//     particle3->setScale(0.90f);
//     m_Particle->addChild(particle2);
//     m_Particle->addChild(particle3);
// 
//     auto action1 = DelayTime::create(1.0f);
//     auto action2 = CallFunc::create(CC_CALLBACK_0(LightningEffect::ExtinctEffect, this));
//     auto action3 = Sequence::create(action1, action2, NULL);
//     m_Particle->runAction(action3);
//     GET_OBJECT_LAYER->addChild(m_Particle, 20);
}

void SwipeEffect::ExtinctEffect()
{
//     GET_OBJECT_LAYER->removeChild(m_Particle);
//     delete this;
}

void SwipeEffect::SetSwipeMotionCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Swipe_SE_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Swipe_SW_NE.plist");
}

void SwipeEffect::ShowSwipeMotionByDir(Direction dir)
{
    switch (dir)
    {
    case SE:    m_RealSprite->runAction(MakeAnimation("Swipe_SE_NW%d.png", 6));        break;
    case SW:    m_RealSprite->runAction(MakeAnimation("Swipe_SW_NE%d.png", 6));        break;
    case NE:    m_RealSprite->runAction(MakeAnimation("Swipe_SW_NE%d.png", 6));        break;
    case NW:    m_RealSprite->runAction(MakeAnimation("Swipe_SE_NW%d.png", 6));        break;
    default:
        break;
    }
}

RepeatForever* SwipeEffect::MakeAnimation(const char* format, int size)
{
    auto animation = Animation::create();
    if (size < 5)       animation->setDelayPerUnit(0.2f);
    else if (size >= 5) animation->setDelayPerUnit(0.1f);

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return RepeatForever::create(Animate::create(animation));
}

