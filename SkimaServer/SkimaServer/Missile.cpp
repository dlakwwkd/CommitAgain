#include "stdafx.h"
#include "Missile.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "UnitPoolManager.h"
#include "ClientSession.h"
#include "Player.h"


Missile::Missile(int unitId)
{
    m_UnitID = SET_MAIN_TYPE(unitId, UNIT_MISSILE);
}


Missile::~Missile()
{
    GUnitPoolManager->Release(this);
}

void Missile::Extinction()
{
	if (m_InUse)
	{
		//CallFuncAfter(1, GObjectManager, &ObjectManager::Except, this);
		CallFuncAfter(1, GUnitPoolManager, &UnitPoolManager::Release, this);
		printf(" Missile::Extinction()!! : UnitID : %d \n", INIT_TYPE(m_UnitID));
	}
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

    m_Owner->GetClient()->ShootBroadCast(m_Owner->GetPlayerID(), m_UnitID, currentPos, m_TargetPos);
    m_State->TryMove(this);
}
