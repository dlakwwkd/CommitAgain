#include "stdafx.h"
#include "Mob.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "UnitPoolManager.h"
#include "ClientSession.h"
#include "Player.h"


Mob::Mob(int unitId)
{
	m_UnitID = SET_MAIN_TYPE(unitId, UNIT_MOB);
}


Mob::~Mob()
{
	GUnitPoolManager->Release(this);
}

void Mob::Extinction()
{
	if (m_InUse)
	{
		//CallFuncAfter(1, GObjectManager, &ObjectManager::Except, this);
		CallFuncAfter(1, GUnitPoolManager, &UnitPoolManager::Release, this);
		printf(" Mob::Extinction()!! : UnitID : %d \n", INIT_TYPE(m_UnitID));
	}
}
