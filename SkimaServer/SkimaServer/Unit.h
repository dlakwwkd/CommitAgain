#pragma once
#include "..\..\PacketType.h"
#include "..\..\FSM.h"

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
	void		SetCurrentPos(b2Vec2 currentPos){ m_CurrentPos = currentPos; }
	void		SetTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	void		SetIsMove(bool isMove){ m_IsMove = isMove; }
	void		SetSpeed(int speed){ m_Speed = speed; }

	void		SetState(MoveState* state){ m_State = state; }
	State*		GetState(){ return (State*)m_State; }
	State*		GetStandbyState() { return (State*)m_StandbyState; }
	State*		GetMovingState(){ return (State*)m_MovingState; }
	State*		GetCrashedState() { return (State*)m_CrashedState; }

	void		TryMove() { m_State->TryMove(this); }
	void		Crashed() { m_State->Crashed(this); }
	void		EndMove() { m_State->EndMove(this); }

	void		UnitMove();
	void		SetAverageMove(b2Vec2 targetPos);

private:
	int			m_ID;
	UnitType	m_Type;
	MoveState*	m_State;

	bool		m_IsMove;
	int			m_Speed;
	b2Vec2		m_AverageMove;
	b2Vec2		m_CurrentPos;
	b2Vec2		m_TargetPos;
	MoveState*	m_StandbyState;
	MoveState*	m_MovingState;
	MoveState*	m_CrashedState;
};

