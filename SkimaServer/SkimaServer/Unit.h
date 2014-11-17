#pragma once
#include "..\..\PacketType.h"
#include "FSM.h"

class b2World;
#define CRASHTIME 0.1f

class Unit
{
public:
	Unit(int playerId, UnitType m_unitType, b2Vec2 pos);
	Unit();
	virtual~Unit();

public:
	int				GetUnitID(){ return m_UnitID; }
	void			SetUnitHp(int Hp){ m_Hp = Hp; }
	int				GetUnitHp(){ return m_Hp; }
	UnitType		GetUnitType(){ return m_UnitType; }
	void			SetSpeed(float speed){ m_Speed = speed; }
	float			GetSpeed(){ return m_Speed; }
	void			SetTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	b2Vec2			GetTargetPos(){ return m_TargetPos; }
	b2Body*			GetBody(){ return m_Body; }

	void			TryMove(b2Vec2 currentPos, b2Vec2 targetPos);
	void			Crashed() { m_State->Crashed(this); }
	void			EndMove() { m_State->EndMove(this); }
	void			EndCrash() { m_State->EndCrash(this); }
	void			Movement(){ m_State->Movement(this); }

	void			SetState(MoveState* state){ m_State = state; }
	MoveState*		GetState(){ return (MoveState*)m_State; }
	MoveState*		GetStandbyState() { return (MoveState*)m_StandbyState; }
	MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*		GetCrashedState() { return (MoveState*)m_CrashedState; }

	void			UnitMove();
	void			Crashing(bool isCrashing);
	//virtual void	UnitCrashed(bool isCrashed)=0;


protected:
	int			m_PlayerID;
	int			m_UnitID; 
	int			m_Hp;
	float		m_Speed; 
	UnitType	m_UnitType; 
	b2Vec2		m_TargetPos; 
	b2Body*		m_Body; 
	
	MoveState*	m_State;
	MoveState*	m_StandbyState;
	MoveState*	m_MovingState;
	MoveState*	m_CrashedState;
};


