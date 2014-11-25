#include "pch.h"
#include "FireballSkill.h"
#include "FireballMissile.h"
#include "GameManager.h"
#include "Hero.h"


FireballSkill::FireballSkill()
{
	m_CoolTime = 5;
	m_CanUse = true;
}

FireballSkill::FireballSkill(Hero* hero)
{
	m_Hero = hero;
	m_CoolTime = 5;
	m_CanUse = true;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillReady()
{
	auto arrow = m_Hero->GetArrow();
	arrow->setVisible(true);
}

void FireballSkill::SkillEnd()
{
	auto arrow = m_Hero->GetArrow();
	arrow->setVisible(false);
}

// 
// void FireballSkill::SkillCast(Point heroPos, Point targetPos, int missileID)
// {
// 	auto missile = GET_MM->Assign(missileID, MS_FIRE_BALL);
// 	missile->MissileCast(heroPos, targetPos);
// }
