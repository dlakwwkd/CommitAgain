#include "pch.h"
#include "SwipeEffect.h"
#include "ObjectLayer.h"
#include "Macros.h"

SwipeEffect::SwipeEffect()
{
    m_RealSprite = Sprite::create("Images/CloackingUnit.png");
    m_RealSprite->setScale(0.3f);
    m_RealSprite->setVisible(true);
    GET_OBJECT_LAYER->addChild(m_RealSprite, 20);
}

SwipeEffect::~SwipeEffect()
{
}

void SwipeEffect::CreateEffect(Vec2 createPos)
{
    m_RealSprite->setPosition(createPos);
    SetSwipeMotionCache();
    auto action1 = DelayTime::create(1.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(SwipeEffect::ExtinctEffect, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_RealSprite->runAction(action3);
}

void SwipeEffect::ExtinctEffect()
{
     GET_OBJECT_LAYER->removeChild(m_RealSprite);
     delete this;
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
    case SE:    m_RealSprite->runAction(MakeAnimationOnce("Swipe_SE_NW%d.png", 6));        break;
    case SW:    m_RealSprite->runAction(MakeAnimationOnce("Swipe_SW_NE%d.png", 6));        break;
    case NE:    m_RealSprite->runAction(MakeAnimationOnce("Swipe_SW_NE%d.png", 6));        break;
    case NW:    m_RealSprite->runAction(MakeAnimationOnce("Swipe_SE_NW%d.png", 6));        break;
    }
}

Animate* SwipeEffect::MakeAnimationOnce(const char* format, int size)
{
    auto animation = Animation::create();
    if (size < 5)       animation->setDelayPerUnit(0.2f);
    else if (size >= 5) animation->setDelayPerUnit(0.1f);

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return Animate::create(animation);
}

