#include "pch.h"
#include "FireWallSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "FireWallEffect.h"


FireWallSkill::FireWallSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 5;
    m_CanUse = true;
}

FireWallSkill::~FireWallSkill()
{
}

void FireWallSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
     auto effect = new FireWallEffect();
     auto direction = GenerateWallDirection(heroPos, targetPos);
     effect->CreateEffect(targetPos,direction);
}

void FireWallSkill::SkillReady()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void FireWallSkill::SkillEnd()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(false);
}

void FireWallSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}

Direction FireWallSkill::GenerateWallDirection(Vec2 heroPos, Vec2 targetPos)
{
    Vec2 displacement = targetPos - heroPos;
    float slope = displacement.y / displacement.x;
    if (slope >= 0)
    {
        return BACKSLASH;
    }
    else
    {
        return SLASH;
    }
}
