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
}

void FireWallEffect::CreateEffect(const Vec2& createPos, Direction direction)
{
    CreateSprite("Images/CloackingUnit.png", createPos, 1.0f, 6.0f);
    SetFireMotionCache();
    ShowFireMotionByDir(direction);
}

void FireWallEffect::ExtinctEffect()
{
    ExtinctSprite();
}

void FireWallEffect::SetFireMotionCache()
{
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FireWall/fire.plist");
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FireWall/fireA.plist");
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FireWall/fireB.plist");
}

void FireWallEffect::ShowFireMotionByDir(Direction dir)
{
    switch (dir)
    {
    case SLASH:     m_Sprite->runAction(MakeFastAnimationForever("fire%02d.png", 25)); break;
    case BACKSLASH: m_Sprite->runAction(MakeFastAnimationForever("fire_A%02d.png", 25)); break;
    
    }
}
