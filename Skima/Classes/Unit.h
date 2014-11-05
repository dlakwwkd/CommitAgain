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



	void			MoveTargeting(Point p);

public:
	PhysicsBody*	GetBody(){ return m_Body; }

protected:
	void			Movement(GameMode gameMode);
	void			SingleMove();
	void			MultiMove();

protected:
	MoveState*		m_MoveState;
	MoveState*		m_StandbyState;
	MoveState*		m_MovingState;
	MoveState*		m_StunnedState;
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

	Point			m_MovePosition;
	bool			m_MoveMode;

protected:
	Sprite*			m_Sprite;
	PhysicsBody*	m_Body;

};