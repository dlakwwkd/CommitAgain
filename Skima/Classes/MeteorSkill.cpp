#include "pch.h"
#include "MeteorSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "ObjectLayer.h"
#include "MeteorSequenceEffect.h"

MeteorSkill::MeteorSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
    m_CautionSprite = Sprite::create("Laphinx/MeteorCaution.png");
}

MeteorSkill::MeteorSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
    m_CautionSprite = Sprite::create("Laphinx/MeteorCaution.png");
}

MeteorSkill::~MeteorSkill()
{
}

void MeteorSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    m_CautionSprite->setScale(0.8f);
    m_CautionSprite->setPosition(targetPos);
    m_CautionSprite->setOpacity(255);
    GET_OBJECT_LAYER->addChild(m_CautionSprite,14);

    auto fadeOut1 = FadeOut::create(0.45f);
    auto fadeIn = FadeIn::create(0.15f);
    auto fadeOut2 = FadeOut::create(0.4f); //total 1.0f //+ meteor 0.2f
    auto fade_seq = Sequence::create(fadeOut1, fadeIn, fadeOut2, NULL);
    m_CautionSprite->runAction(fade_seq);
}

void MeteorSkill::SkillReady()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());
}

void MeteorSkill::SkillEnd()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(false);
}

void MeteorSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}

void MeteorSkill::MakeMeteor(Vec2 targetpos)
{
    auto particleEffect = new MeteorSequenceEffect();
    particleEffect->CreateEffect(targetpos);
}

