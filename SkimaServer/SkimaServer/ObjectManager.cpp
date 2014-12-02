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
    default: ///# ????

    case UNIT_NONE: return nullptr;
    case UNIT_MISSILE:
		///# ��.. �̻��� �Ҵ� ���� ������ O(n)��ŭ �ɸ��µ�... Ǯ�� ������� push/pop�� O(1)�� �ǵ��� ������ ��.
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

	///# ���⿡ ������ �� �ִ� ������ NONE/MISSILE�� �ƴ� ��쵵 �ִµ�.. �װ͵� ����Ȱǰ�?? �ڵ�� ������ ���� �ƴѵ�..
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
    auto player = GGameManager->SearchPlayer(unit->GetPlayerID());
    if (player != nullptr)
    {
        player->UnitListPop(unit->GetUnitID());
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
    default:
    case UNIT_NONE: return nullptr;
    case UNIT_MISSILE: ///# ���ʿ� Ǯ�̶�� ���� ������ �̷��� ��� �߰� �Ҵ��ϴ°� �ƴ϶�, ������ �ڿ��� �������°���..
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

	///# ��.. ��Ŀ�ú��ϰ�?? 
    return Expand(type);
}
