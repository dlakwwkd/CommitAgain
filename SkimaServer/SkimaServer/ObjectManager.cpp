#include "stdafx.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Missile.h"
#include "Player.h"

ObjectManager* GObjectManager = nullptr;

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

Unit* ObjectManager::Assign(UnitType type)
{
    switch (type)
    {
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
    default:
        return nullptr;
    }
    return Expand(type);
}

void ObjectManager::Release(Unit* unit)
{
    unit->m_InUse = false;
    unit->m_UnitID = INIT_SIDE_TYPE(unit->m_UnitID);

    auto body = unit->GetBody();
    if (body != nullptr)
    {
        GGameManager->GetWolrd()->DestroyBody(body);
        unit->InitBody();
    }
    auto player = unit->GetOwner();
    if (player != nullptr)
    {
        player->UnitListPop(unit->GetUnitID());
		unit->m_Owner = nullptr;
    }
}

void ObjectManager::Except(Unit* unit)
{
    auto body = unit->GetBody();
    if (body != nullptr)
    {
        unit->GetBody()->SetActive(false);
    }
}

Unit* ObjectManager::Expand(UnitType type)
{
    switch (type)
    {
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
    default:
        return nullptr;
    }
    return Expand(type);
}
