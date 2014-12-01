#include "pch.h"
#include "ObjectManager.h"
#include "Missile.h"

ObjectManager::ObjectManager()
{
	m_MissileList.reserve(INIT_POOL_SIZE);

	int i;
	for (i = UNIT_MISSILE; i < UNIT_MISSILE + INIT_POOL_SIZE; ++i)
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

Unit* ObjectManager::Assign(UnitType type)
{
	switch (type)
	{
	default:
	case UNIT_NONE: return nullptr;
	case UNIT_MISSILE:
		for (auto& missile : m_MissileList)
		{
			if (!missile->m_InUse)
			{
				missile->m_InUse = true;
				return missile;
			}
		}
		break;
	}
	return Expand(type);
}

void ObjectManager::Release(Unit* unit)
{
	unit->m_InUse = false;
	unit->m_UnitID = unit->m_UnitID & 0xF0FFFFFF;
}

Unit* ObjectManager::Expand(UnitType type)
{
	switch (type)
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
		return m_MissileList.back();
	}
	}
	return Expand(type);
}
