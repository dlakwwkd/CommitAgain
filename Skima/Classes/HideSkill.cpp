#include "pch.h"
#include "HideSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"
#include "HideEffect.h"
#include "ObjectLayer.h"
#include "UnHideEffect.h"
#include "Laphinx.h"
#include "ObjectLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

HideSkill::HideSkill()
{
    m_CoolTime = 9;
    m_HiddenTime = 5;
    m_CanUse = true;
}

HideSkill::HideSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 9;
    m_HiddenTime = 5;
    m_CanUse = true;
}


HideSkill::~HideSkill()
{
}


void HideSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/hide.mp3");
    auto effect = new HideEffect();
    effect->CreateEffect(heroPos);
    m_Hero->SetHeroPerforming(true);
    m_Hero->SetUnitHiddenState(true);

    auto myLaphinxSprite = m_Hero->GetRealSprite();
    auto myHpbar = m_Hero->GetHpBar();
    auto HpFrame = m_Hero->GetHpBarFrame();

    myLaphinxSprite->setOpacity(204);
    myHpbar->setOpacity(204);
    HpFrame->setOpacity(204);
    float lastTime = 0.2f;

    auto spriteDelay = DelayTime::create(lastTime);
    auto hiddenTime = DelayTime::create(m_HiddenTime-lastTime);

    auto laphinx_halfvis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, myLaphinxSprite, 102));
    auto hpbar_halfvis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, myHpbar, 102));
    auto hpFrame_halfvis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 102));
    auto setPerformingFalse = CallFunc::create(CC_CALLBACK_0(Skill::SetHeroPerforming, this, false));

    auto Laphinx_seq = Sequence::create(spriteDelay, laphinx_halfvis,setPerformingFalse, NULL);
    auto Hpbar_seq = Sequence::create(spriteDelay, hpbar_halfvis, NULL);
    auto Hpframe_seq = Sequence::create(spriteDelay, hpFrame_halfvis, NULL);

    myLaphinxSprite->runAction(Laphinx_seq);
    myHpbar->runAction(Hpbar_seq);
    HpFrame->runAction(Hpframe_seq);
}
void HideSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{
    auto effect = new HideEffect();
    effect->CreateEffect(heroPos);
    m_Hero->SetHeroPerforming(true);
    m_Hero->SetUnitHiddenState(true);

    auto enemyLaphinxSprite = m_Hero->GetRealSprite();
    auto enemyHpbar = m_Hero->GetHpBar();
    auto HpFrame = m_Hero->GetHpBarFrame();


    enemyLaphinxSprite->setOpacity(204);
    enemyHpbar->setOpacity(204);
    HpFrame->setOpacity(204);
    float lastTime = 0.1f;

    auto spriteDelay = DelayTime::create(lastTime);

    auto laphinx_halfvis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyLaphinxSprite, 102));
    auto hpbar_halfvis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyHpbar, 102));
    auto hpFrame_halfvis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 102));
    auto laphinx_Invis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyLaphinxSprite, 0));
    auto hpbar_Invis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyHpbar, 0));
    auto hpFrame_Invis = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 0));
    auto setPerformingFalse = CallFunc::create(CC_CALLBACK_0(Skill::SetHeroPerforming, this, false));

    auto Laphinx_seq = Sequence::create(spriteDelay, laphinx_halfvis,spriteDelay,laphinx_Invis, setPerformingFalse, NULL);
    auto Hpbar_seq = Sequence::create(spriteDelay, hpbar_halfvis, spriteDelay,hpbar_Invis, NULL);
    auto Hpframe_seq = Sequence::create(spriteDelay, hpFrame_halfvis, spriteDelay,hpFrame_Invis, NULL);

    enemyLaphinxSprite->runAction(Laphinx_seq);
    enemyHpbar->runAction(Hpbar_seq);
    HpFrame->runAction(Hpframe_seq);
}

void HideSkill::SkillReady()
{

}

void HideSkill::SkillEnd()
{

}
void HideSkill::SetSpriteOpacity(Sprite* sprite, float opacity)
{
    sprite->setOpacity(opacity);
}
