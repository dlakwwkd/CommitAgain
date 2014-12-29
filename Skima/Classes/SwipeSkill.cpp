#include "pch.h"
#include "SwipeSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "SwipeEffect.h"


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

     m_Hero->SetAllSpriteVisible();
     m_Hero->SetUnitHiddenState(false);
}

void SwipeSkill::SkillReady()
{
    auto nearRange = m_Hero->GetNearSkillRange();
    nearRange->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_ATTACK);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void SwipeSkill::SkillEnd()
{
    auto nearRange = m_Hero->GetNearSkillRange();
    nearRange->setVisible(false);
}

void SwipeSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
