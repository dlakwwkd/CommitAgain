#include "pch.h"
#include "IceballSkill.h"
#include "IceballMissile.h"
#include "GameManager.h"


IceballSkill::IceballSkill()
{
	m_CoolTime = 5;
}


IceballSkill::~IceballSkill()
{
}
// 
// void IceballSkill::SkillCast(Point heroPos, Point targetPos, int missileID)
// {
// 	auto missile = GET_MM->Assign(missileID, MS_ICE_BALL);
// 	missile->MissileCast(heroPos, targetPos);
// }
