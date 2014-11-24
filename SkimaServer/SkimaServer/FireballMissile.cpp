#include "stdafx.h"
#include "FireballMissile.h"
#include "GameManager.h"


FireballMissile::FireballMissile(int unitId)
{
	m_MissileType = MS_FIRE_BALL;
	m_UnitID = unitId;
}

FireballMissile::~FireballMissile()
{
}
