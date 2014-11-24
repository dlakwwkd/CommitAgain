#include "stdafx.h"
#include "MissileManager.h"
#include "GameManager.h"
#include "FireballMissile.h"
#include "IceballMissile.h"

MissileManager* GMissileManager = nullptr;

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

Missile* MissileManager::Assign(MissileType type)
{
	for (auto& missile : m_MissileList)
	{
		if (missile->m_MissileType == type && !missile->m_InUse)
		{
			missile->m_InUse = true;
			return missile;
		}
	}

	if (!Expand(type))
	{
		return nullptr;
	}
	return m_MissileList.back();
}

void MissileManager::Release(Missile* missile)
{
	missile->m_InUse = false;
	auto body = missile->GetBody();
	if (body != nullptr)
	{
		GGameManager->GetWolrd()->DestroyBody(body);
	}
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
