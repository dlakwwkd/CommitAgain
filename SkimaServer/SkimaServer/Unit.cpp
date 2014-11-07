#include "stdafx.h"
#include "ClientSession.h"
#include "Unit.h"


Unit::Unit(b2Vec2 pos)
: m_ID(-1), m_Type(TYPE_NONE), m_Speed(5), m_CurrentPos(pos), m_TargetPos({ 0, 0 }),
 m_AverageMove({ 0, 0 })
{
	m_State = m_StandbyState = new StandbyState;
	m_MovingState = new MovingState;
	m_CrashedState = new CrashedState;

	static int makeId = 0;
	m_ID = ++makeId;
}


Unit::~Unit()
{
	delete m_State;
	delete m_StandbyState;
	delete m_MovingState;
	delete m_CrashedState;
}

void Unit::UnitMove()
{
	if (!(m_CurrentPos.x < m_TargetPos.x - 5 ||
		m_CurrentPos.y < m_TargetPos.y - 5 ||
		m_CurrentPos.x > m_TargetPos.x + 5 ||
		m_CurrentPos.y > m_TargetPos.y + 5))
	{
		EndMove();
		return;
	}
	m_CurrentPos = (m_CurrentPos + m_AverageMove);
}

void Unit::SetAverageMove(b2Vec2 targetPos)
{
	auto direction = targetPos - m_CurrentPos;
	auto temp = abs(direction.x) + abs(direction.y);

	direction *= m_Speed / temp;

	m_AverageMove = direction;
}

void Unit::TryMove(b2Vec2 currentPos, b2Vec2 targetPos)
{
	m_CurrentPos = currentPos;
	m_TargetPos = targetPos;
	SetAverageMove(targetPos);
	m_State->TryMove(this);
}
