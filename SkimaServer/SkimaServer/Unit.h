#pragma once
#include "..\..\PacketType.h"
#include "..\..\FSM.h"

class b2World;

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
	void		SetCurrentPos(b2Vec2 currentPos){ m_CurrentPos = currentPos; }
	void		SetTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	void		SetSpeed(int speed){ m_Speed = speed; }

	void		SetState(MoveState* state){ m_State = state; }
	MoveState*	GetState(){ return (MoveState*)m_State; }
	MoveState*	GetStandbyState() { return (MoveState*)m_StandbyState; }
	MoveState*	GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*	GetCrashedState() { return (MoveState*)m_CrashedState; }

	void		TryMove(b2Vec2 currentPos, b2Vec2 targetPos);
	void		Movement(){ m_State->Movement(this); }
	void		Crashed() { m_State->Crashed(this); }
	void		EndMove() { m_State->EndMove(this); }

	void		UnitMove();
	void		SetAverageMove(b2Vec2 targetPos);

private:
	int			m_ID;
	UnitType	m_Type;
	MoveState*	m_State;

	int			m_Speed;
	b2Vec2		m_AverageMove;
	b2Vec2		m_CurrentPos;
	b2Vec2		m_TargetPos;
	MoveState*	m_StandbyState;
	MoveState*	m_MovingState;
	MoveState*	m_CrashedState;
};

