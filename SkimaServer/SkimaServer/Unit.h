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
	b2Vec2		GetAverageMove(){ return m_AverageMove; }
	b2Vec2		GetCurrentPos(){ return m_CurrentPos; }
	b2Vec2		GetTargetPos(){ return m_TargetPos; }
	int			GetSpeed(){ return m_Speed; }
	bool		IsMove(){ return m_IsMove; }
	void		SetAverageMove(b2Vec2 averageMove){ m_AverageMove = averageMove; }
	void		SetCurrentPos(b2Vec2 currentPos){ m_CurrentPos = currentPos; }
	void		SetTargetPos();
	void		SetIsMove(bool isMove){ m_IsMove = isMove; }
	void		SetSpeed(int speed){ m_Speed = speed; }

private:
	int			m_ID;
	UnitType	m_Type;

	bool		m_IsMove;
	int			m_Speed;
	b2Vec2		m_AverageMove;
	b2Vec2		m_CurrentPos;
	b2Vec2		m_TargetPos;
};

