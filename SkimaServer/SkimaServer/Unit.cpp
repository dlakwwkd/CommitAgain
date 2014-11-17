#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Unit.h"


Unit::Unit(int playerId, UnitType m_unitType, b2Vec2 pos)
{
	
}

Unit::Unit()
{
	static int makeId = 0;
	m_UnitID = ++makeId;
	m_unitType = UNIT_NONE;
	m_Hp = 0;

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


void Unit::TryMove(b2Vec2 currentPos, b2Vec2 targetPos)
{
	m_TargetPos = targetPos;

	auto direction = targetPos - m_Body->GetPosition();
	auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

	if (distance < 0.6f)
	{
		m_Body->SetLinearVelocity(b2Vec2(0, 0));
		return;
	}

	direction *= m_Speed / distance;
	m_Body->SetLinearVelocity(direction);

	GClientManager->GetClient(m_PlayerID)->SendHeroInfo(m_UnitID, currentPos, targetPos);

	m_State->TryMove(this);
}


// void Unit::UnitMove()
// {
// 	if (!(m_Body->GetPosition().x < m_TargetPos.x - 0.1f ||
// 		m_Body->GetPosition().y < m_TargetPos.y - 0.1f ||
// 		m_Body->GetPosition().x > m_TargetPos.x + 0.1f ||
// 		m_Body->GetPosition().y > m_TargetPos.y + 0.1f))
// 	{
// 		printf(" - Reach: UnitID:  %d, \t\t\t\t\t X : %.f\tY : %.f\n", m_UnitID,
// 			m_Body->GetPosition().x*PTM_RATIO, m_Body->GetPosition().y*PTM_RATIO);
// 		EndMove();
// 	}
// }
// 
// void Unit::UnitCrashed(bool isCrashed)
// {
// 	auto client = GClientManager->GetClient(m_PlayerID);		_ASSERT(client != nullptr);
// 
// 	auto velo = m_Body->GetLinearVelocity();
// 	velo.x *= 5;
// 	velo.y *= 5;
// 	m_Body->SetLinearVelocity(velo);
// 	auto pos = m_Body->GetPosition();
// 
// 	printf("Velocity unitId: %d, x: %f, y: %f\n", m_UnitID, velo.x*PTM_RATIO, velo.y*PTM_RATIO);
// 
// 	b2Vec2 expectpos;
// 
// 	expectpos.x = pos.x + velo.x * CRASHTIME; //���� ��
// 	expectpos.y = pos.y + velo.y * CRASHTIME;
// 
// 	client->CrashedBroadCast(m_UnitID, m_Body->GetPosition(), expectpos, isCrashed);
// }
