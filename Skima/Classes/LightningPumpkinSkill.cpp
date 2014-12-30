#include "pch.h"
#include "LightningPumpkinSkill.h"
#include "LightningPumpkinEffect.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Macros.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

LightningPumpkinSkill::LightningPumpkinSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 3;
    m_CanUse = true;
    CreateSprite("Images/Interface/lightning.jpg", Vec2(0.103f, 0.135f), Vec2(0.5, 0.5));
}


LightningPumpkinSkill::~LightningPumpkinSkill()
{
}

void LightningPumpkinSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    auto effect = new LightningPumpkinEffect();
    effect->CreateEffect(targetPos);
}

void LightningPumpkinSkill::SkillReady()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void LightningPumpkinSkill::SkillEnd()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(false);
}

void LightningPumpkinSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
