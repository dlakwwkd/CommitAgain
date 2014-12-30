#include "pch.h"
#include "FireWallSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "FireEffect.h"


FireWallSkill::FireWallSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 12;
    m_CanUse = true;
    CreateSprite("Images/Interface/firewall.jpg", Vec2(0.045f, 0.033f), Vec2(0.5, 0.5));
}

FireWallSkill::~FireWallSkill()
{
}

void FireWallSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
     auto effect = new FireEffect();
     //auto direction = GenerateWallDirection(heroPos, targetPos);
     effect->CreateEffect(targetPos);
}

void FireWallSkill::SkillReady()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_SPLASH);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void FireWallSkill::SkillEnd()
{
    auto rangeCircle = m_Owner->GetSkillRange();
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
