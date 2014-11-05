#pragma once
#include "cocos2d.h"
#include "Enums.h"
#include "../../PacketType.h"

USING_NS_CC;

class Unit
{
public:
<<<<<<< HEAD
	Unit(const std::string& filename, Point createPos, float scale, SINGLE_MODE_FUNC);
=======
	Unit(const std::string& filename, Point createPos, float scale, GameMode gameMode);
	~Unit();
>>>>>>> origin/Client_v0.2

	void			SetUnitID(int unitID){ m_UnitID = unitID; }
	void			SetUnitPlayerID(int playerID){ m_PlayerID = playerID; }
	void			SetMoveState(MoveState* moveState) { m_MoveState = moveState; }
	int				GetUnitID(){ return m_UnitID; }
	Sprite*			GetSprite(){ return m_Sprite; }

<<<<<<< HEAD
	void			MoveTargeting(Point p);
	void			Movement(SINGLE_MODE_FUNC);

public:
	Unit(const std::string& filename, Point createPos, float scale, MULTI_MODE_FUNC);

	PhysicsBody*	GetBody(){ return m_Body; }

	void			Movement(MULTI_MODE_FUNC);
=======
	void			SetState(MoveState* state){ m_MoveState = state; }
	MoveState*		GetStandbyState(){ return (MoveState*)m_StandbyState; }
	MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*		GetCrashedState(){ return (MoveState*)m_CrashedState; }
	
	void			MoveTargeting(Point p);

public:
	PhysicsBody*	GetBody(){ return m_Body; }

protected:
	void			Movement(GameMode gameMode);
	void			SingleMove();
	void			MultiMove();
	void			TryMove();
	void			EndMove();
	void			Crashed();
	void			EndCrashed();


protected:
	MoveState*		m_MoveState;
	MoveState*		m_StandbyState;
	MoveState*		m_MovingState;
	MoveState*		m_CrashedState;
>>>>>>> origin/Client_v0.2

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