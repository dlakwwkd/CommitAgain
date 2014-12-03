#include "pch.h"
#include "LightningSkill.h"
#include "GameManager.h"
#include "Hero.h"


LightningSkill::LightningSkill()
{
    m_SkillType = SPLASH_SKILL;
    m_EffectType = EF_LIGHTNING;
    m_CoolTime = 3;
    m_CanUse = true;
}

LightningSkill::LightningSkill(Hero* hero)
{
    m_SkillType = SPLASH_SKILL;
    m_EffectType = EF_LIGHTNING;
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}

LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillReady()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(true);
}

void LightningSkill::SkillEnd()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(false);
}
