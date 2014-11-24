#include "pch.h"
#include "FireballSkill.h"
#include "FireballMissile.h"
#include "GameManager.h"


FireballSkill::FireballSkill()
{
	m_CoolTime = 5;
}


FireballSkill::~FireballSkill()
{
}
// 
// void FireballSkill::SkillCast(Point heroPos, Point targetPos, int missileID)
// {
// 	auto missile = GET_MM->Assign(missileID, MS_FIRE_BALL);
// 	missile->MissileCast(heroPos, targetPos);
// }
