#include "stdafx.h"
#include "Unit.h"


Unit::Unit(b2Vec2 pos)
: m_ID(-1), m_Type(TYPE_NONE), m_Speed(5), m_CurrentPos(pos), m_TargetPos({ 0, 0 }),
m_IsMove(false), m_AverageMove({ 0, 0 })
{
	static int makeId = 0;
	m_ID = ++makeId;
}


Unit::~Unit()
{
}
