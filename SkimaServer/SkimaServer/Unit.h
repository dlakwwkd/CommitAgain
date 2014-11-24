﻿#pragma once
#include "..\..\PacketType.h"
#include "FSM.h"

#define DAMPING 10.0f

class Unit
{
public:
	Unit();
	virtual ~Unit();

public:
	void			SetMaxHp(int MaxHp){ m_MaxHp = MaxHp; }
	void			SetUnitHp(int Hp){ m_Hp = Hp; }
	void			SetSpeed(float speed){ m_Speed = speed; }
	void			SetTargetPos(b2Vec2 targetPos){ m_TargetPos = targetPos; }
	void			SetContectState(bool state){ m_Contacting = state; }

	int				GetPlayerID(){ return m_PlayerID; }
	int				GetUnitID(){ return m_UnitID; }
	int				GetMaxHp(){ return m_MaxHp; }
	int				GetUnitHp(){ return m_Hp; }
	float			GetSpeed(){ return m_Speed; }
	bool			GetContectState(){ return m_Contacting; }
	UnitType		GetUnitType(){ return m_UnitType; }
	b2Vec2			GetTargetPos(){ return m_TargetPos; }
	b2Body*			GetBody(){ return m_Body; }

	void			Moving();
	void			Crashing(bool isCrashing);

	void			TryMove(b2Vec2 currentPos, b2Vec2 targetPos);
	void			Crashed(){ m_State->Crashed(this); }
	void			EndMove(){ m_State->EndMove(this); }
	void			EndCrash(){ m_State->EndCrash(this); }
	void			Movement(){ m_State->Movement(this); }

	void			SetState(MoveState* state){ m_State = state; }
	MoveState*		GetState(){ return (MoveState*)m_State; }
	MoveState*		GetStandbyState(){ return (MoveState*)m_StandbyState; }
	MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*		GetCrashedState(){ return (MoveState*)m_CrashedState; }


protected:
	int			m_PlayerID;
	int			m_UnitID; 
	int			m_MaxHp;
	int			m_Hp;
	float		m_Speed; 
	bool		m_Contacting;
	UnitType	m_UnitType; 
	b2Vec2		m_TargetPos; 
	b2Body*		m_Body; 
	
	MoveState*	m_State;
	MoveState*	m_StandbyState;
	MoveState*	m_MovingState;
	MoveState*	m_CrashedState;
};


