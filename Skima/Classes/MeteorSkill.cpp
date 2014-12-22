#include "pch.h"
#include "MeteorSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"


MeteorSkill::MeteorSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}

MeteorSkill::MeteorSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}

MeteorSkill::~MeteorSkill()
{
}

void MeteorSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
//     auto effect = new LightningEffect();
//     effect->CreateEffect(targetPos);
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
