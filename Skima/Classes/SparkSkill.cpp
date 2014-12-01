#include "pch.h"
#include "SparkSkill.h"
#include "GameManager.h"
#include "Missile.h"
#include "Hero.h"


SparkSkill::SparkSkill()
{
	m_CoolTime = 3;
	m_CanUse = true;
}

SparkSkill::SparkSkill(Hero* hero)
{
	m_Hero = hero;
	m_CoolTime = 3;
	m_CanUse = true;
}

SparkSkill::~SparkSkill()
{
}

void SparkSkill::SkillReady()
{
	auto arrow = m_Hero->GetArrow();
	arrow->setVisible(true);
}

void SparkSkill::SkillEnd()
{
	auto arrow = m_Hero->GetArrow();
	arrow->setVisible(false);
}
