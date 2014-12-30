#include "pch.h"
#include "LightningPumpkinSkill.h"
#include "LightningPumpkinEffect.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Macros.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"
#include "LightningEffect.h"
#include "LightningPumpkinEffect.h"
using namespace CocosDenshion;

LightningPumpkinSkill::LightningPumpkinSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 3;
    m_CanUse = true;
    CreateSprite("Images/Interface/lightning.jpg");
}


LightningPumpkinSkill::~LightningPumpkinSkill()
{
}

void LightningPumpkinSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    auto particleEffect = new LightningEffect();
    particleEffect->CreateEffect(targetPos);
}

void LightningPumpkinSkill::SkillReady()
{
    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());
}

void LightningPumpkinSkill::SkillEnd()
{

}

void LightningPumpkinSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
