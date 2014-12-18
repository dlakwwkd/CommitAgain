#include "stdafx.h"
#include "Missile.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "ClientSession.h"
#include "Player.h"


Missile::Missile()
{
	static int makeId = 0;
	m_UnitID = SET_MAIN_TYPE(++makeId, UNIT_MISSILE);
}


Missile::~Missile()
{
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
