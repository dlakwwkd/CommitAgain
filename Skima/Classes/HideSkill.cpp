#include "pch.h"
#include "HideSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"
#include "HideEffect.h"
#include "ObjectLayer.h"

HideSkill::HideSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}

HideSkill::HideSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}


HideSkill::~HideSkill()
{
}


void HideSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    auto effect = new HideEffect();
    effect->CreateEffect(heroPos);
    m_Hero->SetHeroPerforming(true);

    float lastTime = 0.8f;
    auto myLaphinxSprite = m_Hero->GetRealSprite();
    auto myHpbar = m_Hero->GetMyHpBar();
    auto HpFrame = m_Hero->GetHpBarOut();
    myLaphinxSprite->setOpacity(204);
    myHpbar->setOpacity(204);
    HpFrame->setOpacity(204);
    auto action1 = DelayTime::create(lastTime);
    auto action1sub = DelayTime::create(lastTime);
    auto action1subS = DelayTime::create(lastTime);
    auto action2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this,myLaphinxSprite,102));
    auto action2sub = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, myHpbar, 102));
    auto action2subS = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 102));
    auto action3 = CallFunc::create(CC_CALLBACK_0(Skill::SetHeroPerforming, this, false));
    auto action3sub = Sequence::create(action1sub, action2sub, NULL);
    auto action3subS = Sequence::create(action1subS, action2subS, NULL);
    auto action4 = Sequence::create(action1, action2, action3,NULL);
    myLaphinxSprite->runAction(action4);
    myHpbar->runAction(action3sub);
    HpFrame->runAction(action3subS);
}
void HideSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{
    auto effect = new HideEffect();
    effect->CreateEffect(heroPos);
    
    float lastTime = 0.4f;
    auto enemyLaphinxSprite = m_Hero->GetRealSprite();
    auto enemyHpbar = m_Hero->GetOtherHpBar();
    auto HpFrame = m_Hero->GetHpBarOut();
    enemyLaphinxSprite->setOpacity(204);
    enemyHpbar->setOpacity(204);
    HpFrame->setOpacity(204);
    auto action1 = DelayTime::create(lastTime);
    auto action1sub = DelayTime::create(lastTime);
    auto action1subS = DelayTime::create(lastTime);
    auto action2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyLaphinxSprite, 102));
    auto action2sub = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyHpbar, 102));
    auto action2subS = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 102));
    auto action3 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyLaphinxSprite, 0));
    auto action3sub = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyHpbar, 0));
    auto action3subS = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 0));
    auto action4 = Sequence::create(action1, action2,action3, NULL);
    auto action4sub = Sequence::create(action1sub, action2sub,action3sub, NULL);
    auto action4subS = Sequence::create(action1subS, action2subS, action3subS, NULL);
    enemyLaphinxSprite->runAction(action4);
    enemyHpbar->runAction(action4sub);
    HpFrame->runAction(action4subS);
}

void HideSkill::SkillReady()
{
//     auto moveDir = m_Hero->GetArrow();
//     moveDir->setVisible(true);
}

void HideSkill::SkillEnd()
{
//     auto moveDir = m_Hero->GetArrow();
//     moveDir->setVisible(false);
}

void HideSkill::SetSpriteOpacity(Sprite* sprite, float opacity)
{
    sprite->setOpacity(opacity);
}
