#include "pch.h"
#include "FlashSkill.h"
#include "TeleportEffect.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"


FlashSkill::FlashSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}

FlashSkill::FlashSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}


FlashSkill::~FlashSkill()
{
}


void FlashSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    auto effect = new TeleportEffect();
    effect->CreateEffect(heroPos);
}

void FlashSkill::SkillReady()
{
    auto moveDir = m_Hero->GetArrow();
    moveDir->setVisible(true);
}

void FlashSkill::SkillEnd()
{
    auto moveDir = m_Hero->GetArrow();
    moveDir->setVisible(false);
}

void FlashSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
