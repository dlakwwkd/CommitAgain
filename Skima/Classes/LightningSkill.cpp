#include "pch.h"
#include "LightningSkill.h"
#include "LightningEffect.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"


LightningSkill::LightningSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}

LightningSkill::LightningSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}

LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    auto effect = new LightningEffect();
    effect->CreateEffect(targetPos);
}

void LightningSkill::SkillReady()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void LightningSkill::SkillEnd()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(false);
}

void LightningSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
