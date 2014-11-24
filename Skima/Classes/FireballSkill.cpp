#include "pch.h"
#include "FireballSkill.h"
#include "FireballMissile.h"


FireballSkill::FireballSkill()
{
	m_CoolTime = 5;
	m_Missile = new FireballMissile;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillCast(Point heroPos, Point targetPos, int missileID)
{
	m_Missile->MissileCast(heroPos, targetPos);
}
