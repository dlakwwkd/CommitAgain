#include "pch.h"
#include "FireballSkill.h"
#include "FireballMissile.h"


FireballSkill::FireballSkill()
{
	m_Missile = new FireballMissile;
}


FireballSkill::~FireballSkill()
{
}

void FireballSkill::SkillCast(Point heroPos, Point targetPos)
{
	m_Missile->MissileCast(heroPos, targetPos);
}
