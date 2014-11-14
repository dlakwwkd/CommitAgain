#pragma once
#include "..\..\PacketType.h"
#include "FSM.h"

class b2World;

class Unit
{
public:
	Unit(int playerId, b2Vec2 pos);
	~Unit();

public:
	int			GetUnitID(){ return m_UnitID; }
	UnitType	GetUnitType(){ return m_Type; }
	void		SetSpeed(float speed){ m_Speed = speed; }
	float		GetSpeed(){ return m_Speed; }
	void		SetTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	b2Vec2		GetTargetPos(){ return m_TargetPos; }
	b2Body*		GetBody(){ return m_Body; }

	void		SetState(MoveState* state){ m_State = state; }
	MoveState*	GetState(){ return (MoveState*)m_State; }
	MoveState*	GetStandbyState() { return (MoveState*)m_StandbyState; }
	MoveState*	GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*	GetCrashedState() { return (MoveState*)m_CrashedState; }

	void		TryMove(b2Vec2 currentPos, b2Vec2 targetPos);
	void		Crashed() { m_State->Crashed(this); }
	void		EndMove() { m_State->EndMove(this); }
	void		EndCrash() { m_State->EndCrash(this); }
	void		Movement(){ m_State->Movement(this); }

	void		UnitMove();
	void		UnitCrashed(bool isCrashed);

private:
	int			m_PlayerID;
	int			m_UnitID;
	float		m_Speed;
	UnitType	m_Type;
	b2Vec2		m_TargetPos;
	b2Body*		m_Body;

	MoveState*	m_State;
	MoveState*	m_StandbyState;
	MoveState*	m_MovingState;
	MoveState*	m_CrashedState;
};

