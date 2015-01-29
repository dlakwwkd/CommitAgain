#include "pch.h"
#include "Magician.h"
#include "GameManager.h"
#include "PacketType.h"
#include "FireballSkill.h"
#include "IceballSkill.h"
#include "TeleportSkill.h"
#include "FireWallSkill.h"
#include "Buff.h"

Magician::Magician(Vec2 createPos, float scale)
{
    m_HeroType = HERO_MAGICIAN;
    m_MaxHp = 1200.0f;
    m_CurHp = m_MaxHp;
    m_Speed = 320.0f;
    m_CenterSprite->setPosition(createPos);
    m_CenterSprite->setScale(scale);

    SetMoveMotionToCache();
    SetSkillMotionToCache();

    m_RealSprite = Sprite::createWithSpriteFrameName("MoveMotion_S_03.PNG");
    m_RealSprite->setScale(scale);
    m_RealSprite->setPosition(Vec2(0, 10));
    m_CenterSprite->addChild(m_RealSprite);

    auto shadow = Sprite::create("Images/Unit/unit_shadow.png");
    shadow->setPosition(Vec2(27.5f, 2.5f));
    shadow->setScale(0.75f);
    shadow->setOpacity(150);
    m_RealSprite->addChild(shadow, -2);

    m_SkillList[SKILL_Q] = new FireballSkill(this);
    m_SkillList[SKILL_W] = new IceballSkill(this);
    m_SkillList[SKILL_E] = new TeleportSkill(this);
    m_SkillList[SKILL_R] = new FireWallSkill(this);

    m_Buff = new Buff(this);
}


Magician::~Magician()
{
}

void Magician::SetMoveMotionByDir()
{
    switch (CalcMoveDirection(m_TargetPos - m_CenterSprite->getPosition()))
    {
    case E:  m_RealSprite->runAction(MakeAnimation("MoveMotion_E_%02d.PNG", 7, 0.1f));   	break;
    case W:  m_RealSprite->runAction(MakeAnimation("MoveMotion_W_%02d.PNG", 7, 0.1f));   	break;
    case S:  m_RealSprite->runAction(MakeAnimation("MoveMotion_S_%02d.PNG", 7, 0.1f));   	break;
    case N:  m_RealSprite->runAction(MakeAnimation("MoveMotion_N_%02d.PNG", 7, 0.1f));   	break;
    case SE: m_RealSprite->runAction(MakeAnimation("MoveMotion_SE_%02d.PNG", 7, 0.1f));  	break;
    case SW: m_RealSprite->runAction(MakeAnimation("MoveMotion_SW_%02d.PNG", 7, 0.1f));  	break;
    case NE: m_RealSprite->runAction(MakeAnimation("MoveMotion_NE_%02d.PNG", 7, 0.1f));  	break;
    case NW: m_RealSprite->runAction(MakeAnimation("MoveMotion_NW_%02d.PNG", 7, 0.1f));  	break;
    }
}

void Magician::SetSkillMotionByDir(SkillKey key)
{

}

void Magician::SetMoveMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_E.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_W.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_S.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_N.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Magician/MoveMotion_NW.plist");
}

void Magician::SetSkillMotionToCache()
{

}
