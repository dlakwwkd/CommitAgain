#include "stdafx.h"
#include "ShootingSkill.h"

ShootingSkill::ShootingSkill()
{

}

ShootingSkill::ShootingSkill(int playerid) : m_PlayerId(playerid)
{
	m_Speed = 0;
}

ShootingSkill::~ShootingSkill()
{
}

void ShootingSkill::Shoot(int unitId, b2Vec2 targetPos)
{

}
