#include "pch.h"
#include "FireWallEffect.h"

FireWallEffect::FireWallEffect()
{
}

FireWallEffect::~FireWallEffect()
{
}

void FireWallEffect::CreateEffect(const Vec2& createPos)
{
    CreateSprite("Images/CloackingUnit.png", createPos, 0.3f, 1.0f);
    SetSwipeMotionCache();
}

void FireWallEffect::ExtinctEffect()
{
    ExtinctSprite();
}

void FireWallEffect::SetSwipeMotionCache()
{
//     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Swipe_SE_NW.plist");
//     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Swipe_SW_NE.plist");
}

void FireWallEffect::ShowSwipeMotionByDir(Direction dir)
{
//     switch (dir)
//     {
//     case SE:    m_Sprite->runAction(MakeAnimationOnce("Swipe_SE_NW%d.png", 6)); break;
//     case SW:    m_Sprite->runAction(MakeAnimationOnce("Swipe_SW_NE%d.png", 6)); break;
//     case NE:    m_Sprite->runAction(MakeAnimationOnce("Swipe_SW_NE%d.png", 6)); break;
//     case NW:    m_Sprite->runAction(MakeAnimationOnce("Swipe_SE_NW%d.png", 6)); break;
//     }
}
