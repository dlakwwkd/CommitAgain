#include "stdafx.h"
#include "Unit.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"


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
			curPos.x*PTM_RATIO, curPos.y*PTM_RATIO);
	}
}

void Unit::Crashing(bool isCrashing)
{
	auto client = GClientManager->GetClient(m_PlayerID);
	if (client == nullptr)
	{
		EndCrash();
		printf(" - Crashing Failed ! : playerId is invalid \n");
		return;
	}

	auto curPos = m_Body->GetPosition();
	auto expectPos = curPos;

	if (isCrashing)
	{
		auto velocity = m_Body->GetLinearVelocity();
		velocity *= 5;
		m_Body->SetLinearVelocity(velocity);

		expectPos.x = curPos.x + velocity.x / DAMPING;
		expectPos.y = curPos.y + velocity.y / DAMPING;

		printf(" - Crashing: UnitID:  %d, \t\t\t expectPos: X : %.f\tY : %.f\n", m_UnitID,
			expectPos.x*PTM_RATIO, expectPos.y*PTM_RATIO);
	}
	else
	{
		EndCrash();
		printf(" - CrashEnd: UnitID:  %d, \t\t\t reachPos:  X : %.f\tY : %.f\n", m_UnitID,
			curPos.x*PTM_RATIO, curPos.y*PTM_RATIO);
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
	auto distance = sqrt(pow(displacement.x, 2) + pow(displacement.y, 2));

	if (distance < 0.6f)
	{
		m_Body->SetLinearVelocity(b2Vec2(0, 0));
		return;
	}

	b2Vec2 velocity;
	velocity.x = (displacement.x / distance) * m_Speed;
	velocity.y = (displacement.y / distance) * m_Speed;
	m_Body->SetLinearVelocity(velocity);

	m_TargetPos = targetPos;
	m_State->TryMove(this);

	client->SendHeroInfo(m_UnitID, currentPos, m_TargetPos);
}

