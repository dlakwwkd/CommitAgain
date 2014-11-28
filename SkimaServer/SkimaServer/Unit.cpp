#include "stdafx.h"
#include "Unit.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Scheduler.h"
#include "MissileManager.h"

Unit::Unit()
{
	static int makeId = 0;
	m_UnitID = ++makeId;

	m_PlayerID = -1;
	m_Hp = m_MaxHp = -1;
	m_Damage = 0;
	m_Speed = -1;
	m_Contacting = false;
	m_UnitType = UNIT_NONE;
	m_TargetPos = { -1, -1 };
	m_Body = nullptr;

	m_State = m_StandbyState = new StandbyState;
	m_MovingState = new MovingState;
	m_CrashedState = new CrashedState;
}

Unit::~Unit()
{
	delete m_StandbyState;
	delete m_MovingState;
	delete m_CrashedState;
}


void Unit::Moving()
{
	auto curPos = m_Body->GetPosition();
	if (!(curPos.x < m_TargetPos.x - 0.1f ||
		curPos.y < m_TargetPos.y - 0.1f ||
		curPos.x > m_TargetPos.x + 0.1f ||
		curPos.y > m_TargetPos.y + 0.1f))
	{
		EndMove();
		printf(" - Reach: UnitID:  %d, \t\t\t\t X : %.f\tY : %.f\n", m_UnitID,
            EXTEND(curPos.x), EXTEND(curPos.y));
	}
}

void Unit::Crashing(bool isCrashing)
{
    if (m_UnitType == UNIT_HERO)
    {
        if (m_Hp <= 0) IamDead();
    }
    else if (m_UnitType == UNIT_MISSILE)
    {
        isCrashing = false;
        Extinction();
    }

    auto client = GClientManager->GetClient(m_PlayerID);
    if (client == nullptr)
    {
        EndCrash();
        printf(" - Crashing Failed ! : playerId is invalid \n");
        return;
    }

	auto curPos = m_Body->GetPosition();
    auto velocity = m_Body->GetLinearVelocity();
	auto expectPos = curPos;

	if (isCrashing)
	{
        velocity *= 1.0f / DAMPING;
		expectPos += velocity;
		printf(" - Crashing: UnitID:  %d, \t\t\t expectPos: X : %.f\tY : %.f\n", m_UnitID,
            EXTEND(expectPos.x), EXTEND(expectPos.y));
	} 
	else
	{
		EndCrash();
		printf(" - CrashEnd: UnitID:  %d, \t\t\t reachPos:  X : %.f\tY : %.f\n", m_UnitID,
            EXTEND(curPos.x), EXTEND(curPos.y));
	}

    client->CrashedBroadCast(m_UnitID, m_UnitType, curPos, expectPos, isCrashing);
}


void Unit::TryMove(b2Vec2 currentPos, b2Vec2 targetPos)
{
	auto client = GClientManager->GetClient(m_PlayerID);
	if (client == nullptr)
	{
		printf(" - TryMove Failed ! : playerId is invalid \n");
		return;
	}

	auto displacement = targetPos - m_Body->GetPosition();
    if (displacement.Normalize() < 0.6f)
	{
		m_Body->SetLinearVelocity(b2Vec2(0, 0));
		return;
	}
    displacement *= m_Speed;
    m_Body->SetLinearVelocity(displacement);

	m_TargetPos = targetPos;
	m_State->TryMove(this);

	client->SendHeroInfo(m_UnitID, currentPos, m_TargetPos);
}

void Unit::IamDead()
{

}
