#include "pch.h"
#include "ShootType.h"
#include "Hero.h"


ShootType::ShootType()
{
    m_SkillType = MISSILE_SKILL;
}


ShootType::~ShootType()
{
}

void ShootType::SkillReady()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(true);
}

void ShootType::SkillEnd()
{
    auto arrow = m_Hero->GetArrow();
    arrow->setVisible(false);
}
