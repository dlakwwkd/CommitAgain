#include "stdafx.h"
#include "FireballMissile.h"
#include "GameManager.h"


FireballMissile::FireballMissile(int unitId)
{
	m_MissileType = MS_FIRE_BALL;
	m_UnitID = unitId;
	m_Range = 200.0f;
}


FireballMissile::~FireballMissile()
{
}
