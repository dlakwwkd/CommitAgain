#include "pch.h"
#include "TeleportSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"

TeleportSkill::TeleportSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}
TeleportSkill::TeleportSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 5;
    m_CanUse = true;
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillReady()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(true);
}

void TeleportSkill::SkillEnd()
{
    auto rangeCircle = m_Hero->GetSkillRange();
    rangeCircle->setVisible(false);
}
