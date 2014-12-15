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
//    SetSwipeMotionCache();
    GET_OBJECT_LAYER->addChild(m_RealSprite, 20);
}

void SwipeEffect::ExtinctEffect()
{
     GET_OBJECT_LAYER->removeChild(m_Particle);
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
    default:
        break;
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
