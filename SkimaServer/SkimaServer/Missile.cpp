#include "stdafx.h"
#include "Missile.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "ClientSession.h"
#include "Player.h"


Missile::Missile(int unitId)
{
    m_UnitID = SET_MAIN_TYPE(unitId, UNIT_MISSILE);
    m_Range = 0.0f;
    m_Livetime = 0.0f;
}

Missile::~Missile()
{
    GObjectManager->Release(this);
}

void Missile::MissileShoot()
{
    auto currentPos = m_Body->GetPosition();
    auto displacement = m_TargetPos - currentPos;
    displacement.Normalize();
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

    displacement *= m_Range / m_Speed;
    m_TargetPos = currentPos + displacement;

    m_Owner->GetClient()->MissileBroadCast(m_Owner->GetPlayerID(), m_UnitID, currentPos, m_TargetPos);
    m_State->TryMove(this);
}

void Missile::Extinction()
{
    if (m_InUse)
    {
        //CallFuncAfter(1, GObjectManager, &ObjectManager::Except, this);
        CallFuncAfter(1, GObjectManager, &ObjectManager::Release, this);
        printf("Extinction()!! : UnitID : %d \n", INIT_TYPE(m_UnitID));
    }
}
