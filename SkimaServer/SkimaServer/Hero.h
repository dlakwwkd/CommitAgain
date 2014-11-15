#pragma once
#include "Unit.h"
class Hero : public Unit
{
public:
	Hero();
	Hero(int playerId, b2Vec2 pos);
	~Hero();

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

	void		HeroMove();
	void		HeroCrashed(bool isCrashed);

private:
	int			m_PlayerID;

	MoveState*	m_State;
	MoveState*	m_StandbyState;
	MoveState*	m_MovingState; 
	MoveState*	m_CrashedState;

};

