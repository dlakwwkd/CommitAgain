#include "pch.h"
#include "SwipeEffect.h"

SwipeEffect::SwipeEffect()
{
}

SwipeEffect::~SwipeEffect()
{
}

void SwipeEffect::CreateEffect(const Vec2& createPos)
{
    CreateSprite("Images/Unit/CloackingUnit.png", createPos, 0.3f, 1.0f);
    SetSwipeMotionCache();
}

void SwipeEffect::ExtinctEffect()
{
    ExtinctSprite();
}

void SwipeEffect::SetSwipeMotionCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/Swipe_SE_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/Swipe_SW_NE.plist");
}

void SwipeEffect::ShowSwipeMotionByDir(Direction dir)
{
    switch (dir)
    {
    case SE:    m_Sprite->runAction(MakeAnimation("Swipe_SE_NW%d.png", 6, 0.1f)); break;
    case SW:    m_Sprite->runAction(MakeAnimation("Swipe_SW_NE%d.png", 6, 0.1f)); break;
    case NE:    m_Sprite->runAction(MakeAnimation("Swipe_SW_NE%d.png", 6, 0.1f)); break;
    case NW:    m_Sprite->runAction(MakeAnimation("Swipe_SE_NW%d.png", 6, 0.1f)); break;
    }
}
