#include "pch.h"
#include "FlashSkill.h"
#include "TeleportEffect.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

FlashSkill::FlashSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 3;
    m_CanUse = true;
    CreateSprite("Images/Interface/flash.png");
}


FlashSkill::~FlashSkill()
{
}


void FlashSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/flash.mp3");
    auto effect = new TeleportEffect();
    effect->CreateEffect(heroPos);
}

void FlashSkill::SkillReady()
{
    auto moveDir = m_Owner->GetArrow();
    moveDir->setVisible(true);
}

void FlashSkill::SkillEnd()
{
    auto moveDir = m_Owner->GetArrow();
    moveDir->setVisible(false);
}
