#include "pch.h"
#include "Magician.h"
#include "GameManager.h"
#include "PacketType.h"
#include "FireballSkill.h"
#include "IceballSkill.h"
#include "TeleportSkill.h"


Magician::Magician(Vec2 createPos, float scale)
{
    m_HeroType = HERO_MAGICIAN;
    SetMoveMotionToCache();
    SetSkillMotionToCache();
    m_RealSprite = Sprite::createWithSpriteFrameName("MoveMotion_S_03.PNG");
    m_Sprite->setScale(scale);
    m_Sprite->setPosition(createPos);
    m_RealSprite->setScale(scale);
    m_RealSprite->setPosition(scale*35,scale*35);
    m_Sprite->addChild(m_RealSprite);
    m_Sprite->addChild(m_Arrow);
    m_Sprite->addChild(m_SkillRange);
    auto shadow = Sprite::create("Jupiter/Jupiter_shadow.png");
    shadow->setScale(0.75f);
    shadow->setPosition(Vec2(27.5f, 2.5f));
    shadow->setOpacity(150);
    m_RealSprite->addChild(shadow, -2);

    m_MaxHp = 1000.0f;
    m_CurHp = m_MaxHp;
    SetHpBar();
    m_SkillList[SKILL_Q] = new FireballSkill(this);
    m_SkillList[SKILL_W] = new IceballSkill(this);
    m_SkillList[SKILL_E] = new TeleportSkill(this);

    switch (GET_GM.GetGameMode())
    {
    case SINGLE:
    {
        auto material = PhysicsMaterial(1.0f, 0.6f, 0.8f); // 밀도, 탄성력, 마찰력

        m_Body = PhysicsBody::createCircle(m_Sprite->getContentSize().width*(scale / 2), material);
        m_Body->setMass(1.0f);
        m_Body->setLinearDamping(3);
        m_Body->setRotationEnable(false);

        m_Sprite->setPhysicsBody(m_Body);
        break;
    }
    case MULTI:
        break;
    }
    m_Speed = 360.0f;
}


Magician::~Magician()
{
}

void Magician::SetMoveMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_E.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_W.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_S.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_N.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_NW.plist");
}

void Magician::SetMoveMotionByDir()
{
    switch (CalcMoveDirection(m_TargetPos - m_Sprite->getPosition()))
    {
    case E:  m_RealSprite->runAction(MakeAnimation("MoveMotion_E_%02d.PNG", 7));   	break;
    case W:  m_RealSprite->runAction(MakeAnimation("MoveMotion_W_%02d.PNG", 7));   	break;
    case S:  m_RealSprite->runAction(MakeAnimation("MoveMotion_S_%02d.PNG", 7));   	break;
    case N:  m_RealSprite->runAction(MakeAnimation("MoveMotion_N_%02d.PNG", 7));   	break;
    case SE: m_RealSprite->runAction(MakeAnimation("MoveMotion_SE_%02d.PNG", 7));  	break;
    case SW: m_RealSprite->runAction(MakeAnimation("MoveMotion_SW_%02d.PNG", 7));  	break;
    case NE: m_RealSprite->runAction(MakeAnimation("MoveMotion_NE_%02d.PNG", 7));  	break;
    case NW: m_RealSprite->runAction(MakeAnimation("MoveMotion_NW_%02d.PNG", 7));  	break;
    }
}

void Magician::SetSkillMotionToCache()
{

}

void Magician::SetSkillMotionByDir(SkillKey key)
{

}
