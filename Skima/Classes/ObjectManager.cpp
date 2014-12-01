#include "pch.h"
#include "ObjectManager.h"
#include "Missile.h"

ObjectManager::ObjectManager()
{
	m_MissileList.reserve(INIT_POOL_SIZE);

    int i;
    for (i = 0; i < INIT_POOL_SIZE; ++i)
    {
        m_MissileList.push_back(new Missile(i));
    }
    m_LastID_Missile = i;
}


ObjectManager::~ObjectManager()
{
	for (auto& missile : m_MissileList)
	{
		delete missile;
	}
}

Unit* ObjectManager::Assign(int unitId)
{
    switch (GET_MAIN_TYPE(unitId))
	{
	default:
	case UNIT_NONE: return nullptr;
	case UNIT_MISSILE:
        unitId = INIT_SIDE_TYPE(unitId);
		for (auto& missile : m_MissileList)
		{
            if (missile->m_UnitID == unitId)
			{
				missile->m_InUse = true;
				return missile;
			}
		}
		break;
	}
	return Expand(unitId);
}

void ObjectManager::Release(Unit* unit)
{
	unit->m_InUse = false;
    unit->m_UnitID = INIT_SIDE_TYPE(unit->m_UnitID);
}

Unit* ObjectManager::Expand(int unitId)
{
    switch (GET_MAIN_TYPE(unitId))
	{
	default:
	case UNIT_NONE: return nullptr;
	case UNIT_MISSILE:
	{
		int i;
		for (i = 1 + m_LastID_Missile; i < 1 + m_LastID_Missile + INIT_POOL_SIZE; ++i)
		{
			m_MissileList.push_back(new Missile(i));
		}
		m_LastID_Missile = i;
		return Assign(unitId);
	}
	}
	return Expand(unitId);
}
