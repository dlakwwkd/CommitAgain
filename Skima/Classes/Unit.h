#pragma once
#include "Enums.h"
#include "PacketType.h"
#include "FSM.h"

USING_NS_CC;
typedef std::map<Direction, Animation*> MoveMotion;

class Unit
{
public:
	Unit();
	Unit(const std::string& filename, Point createPos, float scale);
	virtual ~Unit();

	void			SetUnitID(int unitID){ m_UnitID = unitID; }
	void			SetUnitPlayerID(int playerID){ m_PlayerID = playerID; }
	int				GetUnitPlayerID(){ return m_PlayerID; }
	void			SetMoveState(MoveState* moveState) { m_MoveState = moveState; }
	void			SetTargetPos(Point pos){ m_TargetPos = pos; }
	int				GetUnitID(){ return m_UnitID; }
	Sprite*			GetSprite(){ return m_Sprite; }
	Sprite*			GetHpBar(){ return m_HpBar; }
	void			SetMoveMotionByDir();
	void			SetHp(int curHp){ m_CurHp = curHp; }
	float			GetMaxHp(){ return m_MaxHp; }
	void			SetHpBar();
	void			UpdateHpBar();
	Point			GetMoveTargetPos(){ return m_TargetPos; }

	MoveState*		GetMoveState(){ return m_MoveState; }
	MoveState*		GetStandbyState(){ return (MoveState*)m_StandbyState; }
	MoveState*		GetMovingState(){ return (MoveState*)m_MovingState; }
	MoveState*		GetCrashedState(){ return (MoveState*)m_CrashedState; }
	void			TryMove(){ m_MoveState->TryMove(this); }
	void			TryTeleport(){ m_MoveState->TryTeleport(this); }
	void			EndMove(){ m_MoveState->EndMove(this); }
	void			Crashed(){ m_MoveState->Crashed(this); }
	void			EndCrash(){ m_MoveState->EndCrash(this); }
	void			Movement(){ m_MoveState->Movement(this); }

	void			Move();
	void			Crash();
	void			Teleport();

public:
	PhysicsBody*	GetBody(){ return m_Body; }

protected:
	void			MoveS();
	void			MoveM();
	void			CrashS();
	void			CrashM();
	void			TeleportS();
	void			TeleportM();



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
	float			m_MaxHp;
	float			m_CurHp;
	float			m_Speed;

	Point			m_TargetPos;

protected:
	Sprite*			m_Sprite;
	Sprite*			m_HpBar;
	PhysicsBody*	m_Body;
};