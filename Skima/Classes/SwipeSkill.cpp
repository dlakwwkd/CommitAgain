#include "pch.h"
#include "SwipeSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "SwipeEffect.h"


SwipeSkill::SwipeSkill()
{
    m_CoolTime = 1;
    m_CanUse = true;
}

SwipeSkill::SwipeSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 1;
    m_CanUse = true;
}

SwipeSkill::~SwipeSkill()
{
}

void SwipeSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
     auto effect = new SwipeEffect();
     effect->CreateEffect(targetPos);
     
     auto direction = GenerateSkillDirection(targetPos, heroPos);
     effect->ShowSwipeMotionByDir(direction);
}

void SwipeSkill::SkillReady()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void SwipeSkill::SkillEnd()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(false);
}
