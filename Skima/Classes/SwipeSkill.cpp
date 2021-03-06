#include "pch.h"
#include "SwipeSkill.h"
#include "GameManager.h"
#include "UILayer.h"
#include "Hero.h"
#include "Macros.h"
#include "SwipeEffect.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

SwipeSkill::SwipeSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 2;
    m_CanUse = true;
    CreateSprite("Images/Interface/swipe.png");
}

SwipeSkill::~SwipeSkill()
{
}

void SwipeSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
     SimpleAudioEngine::getInstance()->playEffect("Music/Effect/swipe.mp3");
     auto effect = new SwipeEffect();
     effect->CreateEffect(targetPos);
     
     auto direction = GenerateSkillDirection(targetPos, heroPos);
     effect->ShowSwipeMotionByDir(direction);

     m_Owner->SetAllSpriteOpacity(255);
}

void SwipeSkill::SkillReady()
{
    auto nearRange = m_Owner->GetNearSkillRange();
    nearRange->setVisible(true);

    auto uiLayer = GET_UI_LAYER;
    uiLayer->CursorChange(CURSOR_ATTACK);
    uiLayer->GetCurrentCursor()->setPosition(GET_IM->GetMouseLocation());

}

void SwipeSkill::SkillEnd()
{
    auto nearRange = m_Owner->GetNearSkillRange();
    nearRange->setVisible(false);
}
