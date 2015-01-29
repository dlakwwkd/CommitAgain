#include "pch.h"
#include "LightningSkill.h"
#include "LightningEffect.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

LightningSkill::LightningSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 3;
    m_CanUse = true;
    CreateSprite("Images/Interface/lightning.jpg");
}

LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/thunder.mp3");
    auto effect = new LightningEffect();
    effect->CreateEffect(targetPos);
}

void LightningSkill::SkillReady()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setScale(2.1f);
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void LightningSkill::SkillEnd()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(false);
}
