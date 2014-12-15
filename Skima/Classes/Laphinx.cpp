#include "pch.h"
#include "Laphinx.h"
#include "GameManager.h"
#include "PacketType.h"



Laphinx::Laphinx(Vec2 createPos, float scale)
{
    SetMoveMotionToCache();
    SetSkillMotionToCache();
    m_RealSprite = Sprite::createWithSpriteFrameName("Laphinx_S3.png");
    m_Sprite->setScale(scale);
    m_Sprite->setPosition(createPos);
    m_RealSprite->setScale(scale);
    m_RealSprite->setPosition(scale*35,scale*35);
    m_Sprite->addChild(m_RealSprite);
    m_Sprite->addChild(m_Arrow);
    m_Sprite->addChild(m_SkillRange);
//     auto shadow = Sprite::create("Jupiter/Jupiter_shadow.png");
//     shadow->setScale(0.75f);
//     shadow->setPosition(Vec2(27.5f, 2.5f));
//     shadow->setOpacity(150);
//    m_RealSprite->addChild(shadow, -2);

    m_MaxHp = 1000.0f;
    m_CurHp = m_MaxHp;
    SetHpBar();
//     m_SkillList[SKILL_Q] = new FireballSkill(this);
//     m_SkillList[SKILL_W] = new IceballSkill(this);
//     m_SkillList[SKILL_E] = new TeleportSkill(this);

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


Laphinx::~Laphinx()
{
}

void Laphinx::SetMoveMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_E.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_N.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_S.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_W.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/LaphinxMov_SW.plist");
}

void Laphinx::SetMoveMotionByDir()
{
    switch (CalcMoveDirection(m_TargetPos - m_Sprite->getPosition()))
    {
    case E:  m_RealSprite->runAction(MakeAnimation("Laphinx_E%d.png", 8));   	break;
    case W:  m_RealSprite->runAction(MakeAnimation("Laphinx_W%d.png", 8));   	break;
    case S:  m_RealSprite->runAction(MakeAnimation("Laphinx_S%d.png", 8));   	break;
    case N:  m_RealSprite->runAction(MakeAnimation("Laphinx_N%d.png", 8));   	break;
    case SE: m_RealSprite->runAction(MakeAnimation("Laphinx_SE%d.png", 8));  	break;
    case SW: m_RealSprite->runAction(MakeAnimation("Laphinx_SW%d.png", 8));  	break;
    case NE: m_RealSprite->runAction(MakeAnimation("Laphinx_NE%d.png", 8));  	break;
    case NW: m_RealSprite->runAction(MakeAnimation("Laphinx_NW%d.png", 8));  	break;
    }
}

void Laphinx::SetSkillMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_ESkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_ESkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_ESkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_ESkill_SW.plist");
}

void Laphinx::SetSkillMotionByDir(SkillKey key)
{
    switch (key)
    {
    case SKILL_Q:
        //particle visible
        break;

    case SKILL_W:
        break;

    case SKILL_E:
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimation("Laphinx_SE_%d.png", 10)); break;
        case SW: m_RealSprite->runAction(MakeAnimation("Laphinx_SW_%d.png", 10)); break;
        case NE: m_RealSprite->runAction(MakeAnimation("Laphinx_NE_%d.png", 10)); break;
        case NW: m_RealSprite->runAction(MakeAnimation("Laphinx_NW_%d.png", 10)); break;
        }
        break;
    }
}
