#pragma once
#include "cocos2d.h"
#include "Enums.h"
#include "../../PacketType.h"
#include "../../FSM.h"

USING_NS_CC;

class Unit
{
public:
	Unit(const std::string& filename, Point createPos, float scale, GameMode gameMode);
	~Unit();

	void			SetUnitID(int unitID){ m_UnitID = unitID; }
	void			SetUnitPlayerID(int playerID){ m_PlayerID = playerID; }
	void			SetMoveState(MoveState* moveState) { m_MoveState = moveState; }
	int				GetUnitID(){ return m_UnitID; }
	Sprite*			GetSprite(){ return m_Sprite; }

	void			SetState(MoveState* state){ m_MoveState = state; }
	MoveState*		GetStandbyState(){ return (MoveState*)m_StandbyState; }
	MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*		GetCrashedState(){ return (MoveState*)m_CrashedState; }
	
	void			MoveTargeting(Point pos);
	void			Move();
	Point			GetUnitPos(){ return m_CurPos; }

public:
	PhysicsBody*	GetBody(){ return m_Body; }

protected:
	void			MoveS();
	void			MoveM();

	void			TryMove();
	void			EndMove();
	void			Crashed();
	void			EndCrashed();


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
	bool			m_MoveMode;

protected:
	Sprite*			m_Sprite;
	PhysicsBody*	m_Body;
};