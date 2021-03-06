﻿#include "pch.h"
#include "Laphinx.h"
#include "GameManager.h"
#include "PacketType.h"
#include "SwipeSkill.h"
#include "HideSkill.h"
#include "UnHideEffect.h"
#include "HideEffect.h"
#include "ShortDashSkill.h"
#include "MeteorSkill.h"
#include "Buff.h"



Laphinx::Laphinx(Vec2 createPos, float scale)
{
    m_HeroType = HERO_LAPHINX;
    m_MaxHp = 2500.0f;
    m_CurHp = m_MaxHp;
    m_Speed = 350.0f;
    m_CenterSprite->setPosition(createPos);
    m_CenterSprite->setScale(scale);

    SetMoveMotionToCache();
    SetSkillMotionToCache();
    
    m_RealSprite = Sprite::createWithSpriteFrameName("Laphinx_S3.png");
    m_RealSprite->setScale(scale - 0.15f);
    m_RealSprite->setPosition(Vec2(0, 10));
    m_CenterSprite->addChild(m_RealSprite);

//     auto shadow = Sprite::create("Jupiter/Jupiter_shadow.png");
//     shadow->setPosition(Vec2(27.5f, 2.5f));
//     shadow->setScale(0.75f);
//     shadow->setOpacity(150);
//    m_RealSprite->addChild(shadow, -2);

    m_SkillList[SKILL_Q] = new HideSkill(this);
    m_SkillList[SKILL_W] = new ShortDashSkill(this);
    m_SkillList[SKILL_E] = new SwipeSkill(this);
    m_SkillList[SKILL_R] = new MeteorSkill(this);

    m_Buff = new Buff(this);
}


Laphinx::~Laphinx()
{
}

void Laphinx::SetMoveMotionByDir()
{
    switch (CalcMoveDirection(m_TargetPos - m_CenterSprite->getPosition()))
    {
    case E:  m_RealSprite->runAction(MakeAnimation("Laphinx_E%d.png", 8, 0.05f));   	break;
    case W:  m_RealSprite->runAction(MakeAnimation("Laphinx_W%d.png", 8, 0.05f));   	break;
    case S:  m_RealSprite->runAction(MakeAnimation("Laphinx_S%d.png", 8, 0.05f));   	break;
    case N:  m_RealSprite->runAction(MakeAnimation("Laphinx_N%d.png", 8, 0.05f));   	break;
    case SE: m_RealSprite->runAction(MakeAnimation("Laphinx_SE%d.png", 8, 0.05f));  	break;
    case SW: m_RealSprite->runAction(MakeAnimation("Laphinx_SW%d.png", 8, 0.05f));  	break;
    case NE: m_RealSprite->runAction(MakeAnimation("Laphinx_NE%d.png", 8, 0.05f));  	break;
    case NW: m_RealSprite->runAction(MakeAnimation("Laphinx_NW%d.png", 8, 0.05f));  	break;
    }
}

void Laphinx::SetSkillMotionByDir(SkillKey key)
{
    switch (key)
    {
    case SKILL_Q:
        switch (CalcSkillDirection(m_TargetPos - m_CenterSprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_SE%02d.png", 2, 0.2f)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_SW%02d.png", 2, 0.2f)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_NE%02d.png", 2, 0.2f)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_Qskill_NW%02d.png", 2, 0.2f)); break;
        }
        break;

    case SKILL_W:
        break;

    case SKILL_E:
        switch (CalcSkillDirection(m_TargetPos - m_CenterSprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_SE%02d.png", 10, 0.05f)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_SW%02d.png", 10, 0.05f)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_NE%02d.png", 10, 0.05f)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_NW%02d.png", 10, 0.05f)); break;
        }
        break;
    case SKILL_R:
        switch (CalcSkillDirection(m_TargetPos - m_CenterSprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_SE%02d.png", 10, 0.05f)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_SW%02d.png", 10, 0.05f)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_NE%02d.png", 10, 0.05f)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("Laphinx_NW%02d.png", 10, 0.05f)); break;
        }
        break;
    }
}

void Laphinx::SetMoveMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_E.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_N.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_S.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_W.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/LaphinxMov_SW.plist");
}

void Laphinx::SetSkillMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_QSkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_QSkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_QSkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_QSkill_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_ESkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_ESkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_ESkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Laphinx/Laphinx_ESkill_SW.plist");
}
