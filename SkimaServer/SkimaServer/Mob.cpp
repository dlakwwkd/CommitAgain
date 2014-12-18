#include "stdafx.h"
#include "Mob.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "ClientSession.h"
#include "Player.h"


Mob::Mob()
{
	static int makeId = 0;
	m_UnitID = SET_MAIN_TYPE(++makeId, UNIT_MOB);
}


Mob::~Mob()
{
}