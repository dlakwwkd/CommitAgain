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
    m_State = m_MovingState;

    auto currentPos = m_Body->GetPosition();
    auto displacement = m_TargetPos - currentPos;
    displacement.Normalize();
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

    displacement *= m_Range / m_Speed;
    m_TargetPos = currentPos + displacement;

    m_Owner->GetClient()->ShootBroadCast(m_Owner->GetPlayerID(), m_UnitID, currentPos, m_TargetPos);
}

void Missile::MissileExplosion()
{
    auto curPos = m_Body->GetPosition();
    auto scale = Reduce(80.0f);
    Rect range;
    range.m_Top = curPos.y + scale;
    range.m_Bottom = curPos.y - scale;
    range.m_Left = curPos.x - scale;
    range.m_Right = curPos.x + scale;

    GGameManager->FieldDamage(m_Owner, &range, m_Damage);

    m_IsDead = true;
    CallFuncAfter(1, GGameManager, &GameManager::DeadUnit, this);
    printf(" - CallFuncAfter: DeadUnit : MainType: %d, SideType: %d, UnitID: %d\n", GET_MAIN_TYPE(m_UnitID), GET_SIDE_TYPE(m_UnitID), INIT_TYPE(m_UnitID));
    EndCrash();
}
