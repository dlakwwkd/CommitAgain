﻿#pragma once
#include "Enums.h"
#include "PacketType.h"
#include "FSM.h"

USING_NS_CC;
typedef std::map<Direction, Animate*> MoveMotion;

class Unit
{
public:
	Unit();
	Unit(const std::string& filename, Point createPos, float scale);
	virtual ~Unit();

	void			SetUnitID(int unitID){ m_UnitID = unitID; }
	void			SetUnitPlayerID(int playerID){ m_PlayerID = playerID; }
	void			SetMoveState(MoveState* moveState) { m_MoveState = moveState; }
	void			SetMoveTargetPos(Point pos){ m_TargetPos = pos; }
	int				GetUnitID(){ return m_UnitID; }
	Sprite*			GetSprite(){ return m_Sprite; }
	Sprite*			GetHpBar(){ return m_HpBar; }
	virtual void	SetMoveMotionByDir() = 0;
	void			SetHpBar(Point unitPos);
	void			UpdateHpBar();
	Point			GetMoveTargetPos(){ return m_TargetPos; }

	MoveState*		GetMoveState(){ return m_MoveState; }
	MoveState*		GetStandbyState(){ return (MoveState*)m_StandbyState; }
	MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*		GetCrashedState(){ return (MoveState*)m_CrashedState; }
	void			TryMove(){ m_MoveState->TryMove(this); }
	void			EndMove(){ m_MoveState->EndMove(this); }
	void			Crashed(){ m_MoveState->Crashed(this); }
	void			EndCrash(){ m_MoveState->EndCrash(this); }
	void			Movement(){ m_MoveState->Movement(this); }

	void			Move();
	void			Crash();

public:
	PhysicsBody*	GetBody(){ return m_Body; }

protected:
	void			MoveS();
	void			MoveM();
	void			CrashS();
	void			CrashM();


protected:
	MoveState*		m_MoveState;
	MoveState*		m_StandbyState;
	MoveState*		m_MovingState;
	MoveState*		m_CrashedState;

protected:
	MoveMotion		m_MoveMotionByDir;
	UnitType		m_UnitType;
	std::string		m_Name;
	int				m_PlayerID;
	int				m_UnitID;
	int				m_MaxHp;
	int				m_Hp;
	float			m_Speed;

	Point			m_TargetPos;

protected:
	Sprite*			m_Sprite;
	Sprite*			m_HpBar;
	PhysicsBody*	m_Body;
};