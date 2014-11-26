#pragma once
class Unit;

class State
{
};
class MoveState : public State
{
public:
	virtual ~MoveState(){}
	virtual void TryTeleport(Unit* unit) = 0;
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
	virtual void TryTeleport(Unit* unit);
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
	virtual void TryTeleport(Unit* unit);
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
	virtual void TryTeleport(Unit* unit);
	virtual void TryMove(Unit* unit);
	virtual void Crashed(Unit* unit);
	virtual void EndMove(Unit* unit);
	virtual void EndCrash(Unit* unit);
	virtual void Movement(Unit* unit);
};