#include "pch.h"
#include "Mob.h"
#include "GameManager.h"
#include "ObjectLayer.h"



Mob::Mob(Vec2 createPos, float scale, int hp, float speed)
{
    m_UnitType = UNIT_MOB;
    m_MaxHp = hp;
    m_CurHp = m_MaxHp;
    m_Speed = speed;
    m_CenterSprite->setPosition(createPos);
    m_CenterSprite->setScale(scale);

    m_RealSprite = Sprite::create("Images/Unit/Mob/MobImage.png");
    m_RealSprite->setScale(scale*0.8f);
    m_CenterSprite->addChild(m_RealSprite);

    SetMoveMotionToCache();
}


Mob::~Mob()
{
}

void Mob::SetMoveMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_E.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_S.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_W.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_N.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Mob/Mob_SW.plist");
}

void Mob::SetMoveMotionByDir()
{
    switch (CalcMoveDirection(m_TargetPos - m_CenterSprite->getPosition()))
    {
    case E:  m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_E%02d.png", 8));   	break;
    case W:  m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_W%02d.png", 8));   	break;
    case S:  m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_S%02d.png", 8));   	break;
    case N:  m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_N%02d.png", 8));   	break;
    case SE: m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_SE%02d.png", 8));  	break;
    case SW: m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_SW%02d.png", 8));  	break;
    case NE: m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_NE%02d.png", 8));  	break;
    case NW: m_RealSprite->runAction(MakeUnitAnimationOnce("Mob_NW%02d.png", 8));  	break;
    }
}
