#include "pch.h"
#include "FlashSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"


FlashSkill::FlashSkill()
{
    m_SkillType = MOVEMENT_SKILL;
    m_EffectType = EF_TELE;
    m_CoolTime = 3;
    m_CanUse = true;
}

FlashSkill::FlashSkill(Hero* hero)
{
    m_Hero = hero;
    m_SkillType = MOVEMENT_SKILL;
    m_EffectType = EF_TELE;
    m_CoolTime = 3;
    m_CanUse = true;
}


FlashSkill::~FlashSkill()
{
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