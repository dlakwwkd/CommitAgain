#include "pch.h"
#include "MeteorSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "ObjectLayer.h"
#include "MeteorEffect.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

MeteorSkill::MeteorSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 6;
    m_CanUse = true;
    m_CautionSprite = Sprite::create("Images/Effect/MeteorCaution.png");
    m_CautionSprite->setScale(1.5f);
    m_CautionSprite->setOpacity(0);
    GET_OBJECT_LAYER->addChild(m_CautionSprite, 14);
    CreateSprite("Images/Interface/Meteor_icon.png");

}

MeteorSkill::~MeteorSkill()
{
}

void MeteorSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    m_CautionSprite->setPosition(targetPos);
    m_CautionSprite->setOpacity(255);

    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/meteor_shoot.mp3");


    auto fadeOut1 = FadeOut::create(0.3f);
    auto fadeIn = FadeIn::create(0.2f);
    auto fadeOut2 = FadeOut::create(0.2f); //total 1.2
    auto fade_seq = Sequence::create(fadeOut1, fadeIn, fadeOut2, NULL);
    m_CautionSprite->runAction(fade_seq);
}

void MeteorSkill::SkillReady()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setScale(2.0f);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());
}

void MeteorSkill::SkillEnd()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(false);
}


void MeteorSkill::MakeMeteor(Vec2 targetpos)
{
    auto particleEffect = new MeteorEffect(); // particle
    particleEffect->CreateEffect(targetpos); //explode sprite
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/meteor_hit.mp3"); //파티클이 끝나기도 전에 터져 버림
}

