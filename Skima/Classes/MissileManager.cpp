#include "pch.h"
#include "MissileManager.h"
#include "FireballMissile.h"
#include "IceballMissile.h"

MissileManager::MissileManager()
{
	m_MissileList.reserve(InitPoolSize::TOTAL);

	int i, unitId;

	for (i = 0; i < InitPoolSize::FIRE_BALL; ++i)
	{
		unitId = IDBoundary::FIRE_BALL_ID_START + i;
		m_MissileList.push_back(new FireballMissile(unitId));
	}
	m_LastID_FireBall = unitId;

	for (i = 0; i < InitPoolSize::ICE_BALL; ++i)
	{
		unitId = IDBoundary::ICE_BALL_ID_START + i;
		m_MissileList.push_back(new IceballMissile(unitId));
	}
	m_LastID_IceBall = unitId;
}


MissileManager::~MissileManager()
{
	for (auto& missile : m_MissileList)
	{
		delete missile;
	}
}

Missile* MissileManager::Assign(int unitId, MissileType type)
{
	if (unitId < 0)
	{
		return nullptr;
	}

	for (auto& missile : m_MissileList)
	{
		if (missile->m_UnitID == unitId)
		{
			missile->m_InUse = true;
			return missile;
		}
	}

	if (!Expand(type))
	{
		return nullptr;
	}
	return Assign(unitId, type);
}

void MissileManager::Release(Missile* missile)
{
	missile->m_InUse = false;
}

bool MissileManager::Expand(MissileType type)
{
	int i, unitId;

	switch (type)
	{
	case MS_NONE:
		return false;
		break;
	case MS_FIRE_BALL:
		for (i = 1; i < InitPoolSize::FIRE_BALL; ++i)
		{
			unitId = m_LastID_FireBall + i;
			m_MissileList.push_back(new FireballMissile(unitId));
		}
		m_LastID_FireBall = unitId;
		break;
	case MS_ICE_BALL:
		for (i = 1; i < InitPoolSize::ICE_BALL; ++i)
		{
			unitId = m_LastID_IceBall + i;
			m_MissileList.push_back(new IceballMissile(unitId));
		}
		m_LastID_IceBall = unitId;
		break;
	}
	return true;
}
