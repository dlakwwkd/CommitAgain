#include "stdafx.h"
#include "Unit.h"


Unit::Unit(b2Vec2 pos)
: m_ID(-1), m_Type(TYPE_NONE), m_Speed(0), m_CurrentPos({ 0, 0 }), m_TargetPos({ 0, 0 })
{
	static int makeId = 0;
	m_ID = ++makeId;
	m_CurrentPos = pos;
}


Unit::~Unit()
{
}
