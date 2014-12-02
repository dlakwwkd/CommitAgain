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
		///# 헐.. 미사일 할당 받을 때마다 O(n)만큼 걸리는데... 풀을 만드려면 push/pop이 O(1)이 되도록 만들어야 함.
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

	///# 여기에 진입할 수 있는 조건이 NONE/MISSILE이 아닌 경우도 있는데.. 그것도 고려된건가?? 코드로 봐서는 전혀 아닌데..
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
    case UNIT_MISSILE: ///# 애초에 풀이라는 것의 개념은 이렇게 계속 추가 할당하는게 아니라, 유한한 자원을 돌려쓰는것임..
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

	///# 헐.. 리커시브하게?? 
    return Expand(type);
}
