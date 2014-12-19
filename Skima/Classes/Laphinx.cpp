#include "pch.h"
#include "Laphinx.h"
#include "GameManager.h"
#include "PacketType.h"
#include "SwipeSkill.h"
#include "AdrenalineSkill.h"
#include "HideSkill.h"


Laphinx::Laphinx(Vec2 createPos, float scale)
{
	m_HeroType = HERO_LAPHINX;
	m_MaxHp = 1000.0f;
	m_CurHp = m_MaxHp;
	m_Speed = 360.0f;
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);

    SetMoveMotionToCache();
    SetSkillMotionToCache();
    
	m_RealSprite = Sprite::createWithSpriteFrameName("Laphinx_S3.png");
    m_RealSprite->setScale(scale);
	m_RealSprite->setAnchorPoint(Vec2(0, 0));
	m_RealSprite->setPosition(-50, -50);
	m_Sprite->addChild(m_RealSprite);

//     auto shadow = Sprite::create("Jupiter/Jupiter_shadow.png");
//     shadow->setPosition(Vec2(27.5f, 2.5f));
//     shadow->setScale(0.75f);
//     shadow->setOpacity(150);
//    m_RealSprite->addChild(shadow, -2);

    m_Qparticle = ParticleSystemQuad::create("Laphinx/LaphinxSpeedParticle.plist");
    m_Qparticle->setPosition(Vec2(30.0f, 25.0f));
    m_Qparticle->setScale(0.7f);
    m_Qparticle->setVisible(false);
    m_RealSprite->addChild(m_Qparticle, -1);

    m_SkillList[SKILL_Q] = new HideSkill(this);
//     m_SkillList[SKILL_W] = new IceballSkill(this);
    m_SkillList[SKILL_E] = new SwipeSkill(this);
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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_QSkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_QSkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_QSkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Laphinx/Laphinx_QSkill_SW.plist");
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
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_SE%02d.png", 2)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_SW%02d.png", 2)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_NE%02d.png", 2)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_NW%02d.png", 2)); break;
        }
        break;

    case SKILL_W:
        break;

    case SKILL_E:
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_SE%02d.png", 10)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_SW%02d.png", 10)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_NE%02d.png", 10)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_NW%02d.png", 10)); break;
        }
        break;
    }
}
