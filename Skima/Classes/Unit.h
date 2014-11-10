#pragma once
#include "cocos2d.h"
#include "Enums.h"
#include "../../PacketType.h"
#include "../../FSM.h"

USING_NS_CC;

class Unit
{
public:
	Unit(const std::string& filename, Point createPos, float scale);
	~Unit();

	void			SetUnitID(int unitID){ m_UnitID = unitID; }
	void			SetUnitPlayerID(int playerID){ m_PlayerID = playerID; }
	void			SetMoveState(MoveState* moveState) { m_MoveState = moveState; }
	void			SetMoveTargetPos(Point pos){ m_TargetPos = pos; }
	int				GetUnitID(){ return m_UnitID; }
	Sprite*			GetSprite(){ return m_Sprite; }
	Point			GetUnitPos(){ return m_CurPos; }

	MoveState*		GetMoveState(){ return m_MoveState; }
	MoveState*		GetStandbyState(){ return (MoveState*)m_StandbyState; }
	MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*		GetCrashedState(){ return (MoveState*)m_CrashedState; }
	
	void			Move();
	void			Crash();

	void			TryMove();
	void			EndMove();
	void			Crashed();
	void			EndCrashed();
	void			Movement();


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
	UnitType		m_UnitType;
	std::string		m_Name;
	int				m_PlayerID;
	int				m_UnitID;
	int				m_MaxHp;
	int				m_MaxMp;
	int				m_Hp;
	int				m_Mp;
	float			m_Speed;

	Point			m_CurPos;
	Point			m_TargetPos;

protected:
	Sprite*			m_Sprite;
	PhysicsBody*	m_Body;
};