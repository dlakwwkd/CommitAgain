#include "stdafx.h"
#include "UnitPoolManager.h"
#include "GameManager.h"
#include "Missile.h"
#include "Mob.h"
#include "Player.h"

UnitPoolManager* GUnitPoolManager = nullptr;

UnitPoolManager::UnitPoolManager()
{
	m_UnitPoolList.reserve(INIT_POOL_SIZE*10);

    for (int i = 0; i < INIT_POOL_SIZE; ++i)
    {
		m_UnitPoolList.insert(UnitPoolList::value_type(UNIT_MISSILE, new Missile()));
		m_UnitPoolList.insert(UnitPoolList::value_type(UNIT_MOB, new Mob()));
    }
}


UnitPoolManager::~UnitPoolManager()
{
	for (auto& missile : m_UnitPoolList)
    {
        delete missile.second;
    }
}

Unit* UnitPoolManager::Assign(UnitType type)
{
	auto iter = m_UnitPoolList.find(type);
	if (iter != m_UnitPoolList.end())
	{
		auto unit = iter->second;
		m_UnitPoolList.erase(iter);
		unit->m_InUse = true;
		return unit;
	}
    return Expand(type);
}

void UnitPoolManager::Release(Unit* unit)
{
	unit->m_InUse = false;
	unit->m_UnitID = INIT_SIDE_TYPE(unit->m_UnitID);

	if (unit->m_Body != nullptr)
    {
		GGameManager->GetWolrd()->DestroyBody(unit->m_Body);
		unit->m_Body = nullptr;
    }
	if (unit->m_Owner != nullptr)
    {
		unit->m_Owner->UnitListPop(unit->m_UnitID);
		unit->m_Owner = nullptr;
    }
	m_UnitPoolList.insert(UnitPoolList::value_type(UnitType(GET_MAIN_TYPE(unit->m_UnitID)), unit));
}

void UnitPoolManager::Except(Unit* unit)
{
	auto body = unit->GetBody();
	if (body != nullptr)
	{
		unit->GetBody()->SetActive(false);
	}
}

Unit* UnitPoolManager::Expand(UnitType type)
{
	switch (type)
    {
    case UNIT_MISSILE:
		for (int i = 0; i < INIT_POOL_SIZE; ++i)
		{
			m_UnitPoolList.insert(UnitPoolList::value_type(UNIT_MISSILE, new Missile()));
		}
		break;
	case UNIT_MOB:
		for (int i = 0; i < INIT_POOL_SIZE; ++i)
		{
			m_UnitPoolList.insert(UnitPoolList::value_type(UNIT_MOB, new Mob()));
		}
		break;
	default:
        return nullptr;
    }
	return Assign(type);
}
