#pragma once
#include "..\..\PacketType.h"

class Unit
{
public:
	Unit(b2Vec2 pos);
	~Unit();

public:
	int			GetUnitID(){ return m_ID; }
	UnitType	GetUnitType(){ return m_Type; }
	b2Vec2		GetCurrentPos(){ return m_CurrentPos; }
	b2Vec2		GetTargetPos(){ return m_TargetPos; }
	void		SetCurrentPos();
	void		SetTargetPos();

private:
	int			m_ID;
	UnitType	m_Type;

	int			m_Speed;
	b2Vec2		m_CurrentPos;
	b2Vec2		m_TargetPos;
};

