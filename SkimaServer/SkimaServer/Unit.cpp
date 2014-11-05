#include "stdafx.h"
#include "Unit.h"


Unit::Unit(b2Vec2 pos)
: m_ID(-1), m_Type(TYPE_NONE), m_Speed(5), m_CurrentPos(pos), m_TargetPos({ 0, 0 }),
m_IsMove(false), m_AverageMove({ 0, 0 })
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
		m_IsMove = false;
		return;
	}
	m_CurrentPos = (m_CurrentPos + m_AverageMove);
}

void Unit::SetAverageMove(b2Vec2 targetPos)
{
	m_IsMove = true;
	auto direction = targetPos - m_CurrentPos;
	auto temp = abs(direction.x) + abs(direction.y);

	direction *= m_Speed / temp;

	m_AverageMove = direction;
}