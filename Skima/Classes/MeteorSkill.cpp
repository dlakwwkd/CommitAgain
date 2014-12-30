#include "pch.h"
#include "MeteorSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "ObjectLayer.h"
#include "MeteorSequenceEffect.h"

MeteorSkill::MeteorSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 10;
    m_CanUse = true;
    m_CautionSprite = Sprite::create("Images/Effect/MeteorCaution.png");
    m_CautionSprite->setScale(0.8f);
    m_CautionSprite->setOpacity(0);
    GET_OBJECT_LAYER->addChild(m_CautionSprite, 14);
    CreateSprite("Images/Interface/Meteor_icon.png", Vec2(0.5f, 0.7f), Vec2(0.5, 0.5));

}

MeteorSkill::~MeteorSkill()
{
}

void MeteorSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    m_CautionSprite->setPosition(targetPos);
    m_CautionSprite->setOpacity(255);

    auto fadeOut1 = FadeOut::create(0.45f);
    auto fadeIn = FadeIn::create(0.15f);
    auto fadeOut2 = FadeOut::create(0.4f); //total 1.2f = caution 1.0f + particle 0.2f
    auto fade_seq = Sequence::create(fadeOut1, fadeIn, fadeOut2, NULL);
    m_CautionSprite->runAction(fade_seq);
}

void MeteorSkill::SkillReady()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());
}

void MeteorSkill::SkillEnd()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(false);
}

void MeteorSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}

void MeteorSkill::MakeMeteor(Vec2 targetpos)
{
    auto particleEffect = new MeteorSequenceEffect(targetpos); // particle
    particleEffect->CreateEffect(targetpos); //explode sprite
}

