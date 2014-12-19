#include "pch.h"
#include "HideSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"
#include "HideEffect.h"
#include "ObjectLayer.h"

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

    auto vis1 = DelayTime::create(m_HiddenTime);
    auto vis2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, myLaphinxSprite, 255));
    auto vis3 = Sequence::create(vis1, vis2, NULL);
    auto visSub1 = DelayTime::create(m_HiddenTime);
    auto visSub2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, myHpbar, 255));
    auto visSub3 = Sequence::create(visSub1, visSub2, NULL);
    auto visSubS1 = DelayTime::create(m_HiddenTime);
    auto visSubS2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 255));
    auto visSubS3 = Sequence::create(visSubS1, visSubS2, NULL);
    myLaphinxSprite->runAction(vis3);
    myHpbar->runAction(visSub3);
    HpFrame->runAction(visSubS3);

    auto pause1 = DelayTime::create(m_HiddenTime - 0.05f);
    auto pause2 = CallFunc::create(CC_CALLBACK_0(Skill::SetHeroPerforming, this, true));
    auto pause3 = Sequence::create(pause1, pause2, NULL);
    myLaphinxSprite->runAction(pause3);

    auto after1 = DelayTime::create(m_HiddenTime+0.02f);
    auto after2 = CallFunc::create(CC_CALLBACK_0(Skill::SetHeroPerforming, this, false));
    auto after3 = Sequence::create(after1, after2, NULL);
    myLaphinxSprite->runAction(after3);

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

    auto vis1 = DelayTime::create(m_HiddenTime);
    auto vis2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyLaphinxSprite, 255));
    auto vis3 = Sequence::create(vis1, vis2, NULL);
    auto visSub1 = DelayTime::create(m_HiddenTime);
    auto visSub2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, enemyHpbar, 255));
    auto visSub3 = Sequence::create(visSub1, visSub2, NULL);
    auto visSubS1 = DelayTime::create(m_HiddenTime);
    auto visSubS2 = CallFunc::create(CC_CALLBACK_0(HideSkill::SetSpriteOpacity, this, HpFrame, 255));
    auto visSubS3 = Sequence::create(visSubS1, visSubS2, NULL);
    enemyLaphinxSprite->runAction(vis3);
    enemyHpbar->runAction(visSub3);
    HpFrame->runAction(visSubS3);

//     auto pause1 = DelayTime::create(m_HiddenTime - 0.1f);
//     auto pause2 = CallFunc::create(CC_CALLBACK_0(Skill::SetHeroPerforming, this, false));
//     auto pause3 = Sequence::create(pause1, pause2, NULL);
//     e->runAction(pause3);
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