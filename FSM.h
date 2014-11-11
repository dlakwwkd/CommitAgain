#pragma once

class Unit;

///# FSM.h가 있으면 FSM.cpp에서 구현하는게 기본인데.. UnitState.cpp에 구현이 있는 이유는?
///# 그리고... 이게 왜 네트워크 필터에 있는지??

class State
{
};

class MoveState : public State
{
public:
	virtual ~MoveState(){}
	virtual void TryMove(Unit* unit) = 0;
	virtual void Crashed(Unit* unit) = 0;
	virtual void EndMove(Unit* unit) = 0;
	virtual void EndCrash(Unit* unit) = 0;
	virtual void Movement(Unit* unit) = 0;
};

class StandbyState : public MoveState
{
public:
	virtual ~StandbyState(){}
	virtual void TryMove(Unit* unit);
	virtual void Crashed(Unit* unit);
	virtual void EndMove(Unit* unit);
	virtual void EndCrash(Unit* unit);
	virtual void Movement(Unit* unit);
};
class MovingState : public MoveState
{
public:
	virtual ~MovingState(){}
	virtual void TryMove(Unit* unit);
	virtual void Crashed(Unit* unit);
	virtual void EndMove(Unit* unit);
	virtual void EndCrash(Unit* unit);
	virtual void Movement(Unit* unit);
};
class CrashedState : public MoveState
{
public:
	virtual ~CrashedState(){}
	virtual void TryMove(Unit* unit);
	virtual void Crashed(Unit* unit);
	virtual void EndMove(Unit* unit);
	virtual void EndCrash(Unit* unit);
	virtual void Movement(Unit* unit);
};