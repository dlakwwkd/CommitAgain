#include "pch.h"
#include "IceballSkill.h"
#include "IceballMissile.h"
#include "GameManager.h"
#include "Hero.h"


IceballSkill::IceballSkill()
{
	m_CoolTime = 5;
	m_CanUse = true;
}

IceballSkill::IceballSkill(Hero* hero)
{
	m_Hero = hero;
	m_CoolTime = 5;
	m_CanUse = true;
}

IceballSkill::~IceballSkill()
{
}

void IceballSkill::SkillReady()
{
	auto arrow = m_Hero->GetArrow();
	arrow->setVisible(true);
}

void IceballSkill::SkillEnd()
{
	auto arrow = m_Hero->GetArrow();
	arrow->setVisible(false);
}

// 
// void IceballSkill::SkillCast(Point heroPos, Point targetPos, int missileID)
// {
// 	auto missile = GET_MM->Assign(missileID, MS_ICE_BALL);
// 	missile->MissileCast(heroPos, targetPos);
// }
