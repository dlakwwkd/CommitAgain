#pragma once

class State
{
};

class MoveState : public State
{
public:
	virtual void TryMove()	= 0;
	virtual void Stunned()	= 0;
	virtual void Crashed()	= 0;

	virtual void EndMove()	= 0;
	virtual void EndStun()	= 0;
	virtual void EndCrash() = 0;
};

class StandbyState : public MoveState
{
public:
	virtual void TryMove();
	virtual void Stunned();
	virtual void Crashed();

	virtual void EndMove();
	virtual void EndStun();
	virtual void EndCrash();
};
class MovingState : public MoveState
{
public:
	virtual void TryMove();
	virtual void Stunned();
	virtual void Crashed();

	virtual void EndMove();
	virtual void EndStun();
	virtual void EndCrash();
};
class StunnedState : public MoveState
{
public:
	virtual void TryMove();
	virtual void Stunned();
	virtual void Crashed();

	virtual void EndMove();
	virtual void EndStun();
	virtual void EndCrash();
};
class CrashedState : public MoveState
{
public:
	virtual void TryMove();
	virtual void Stunned();
	virtual void Crashed();

	virtual void EndMove();
	virtual void EndStun();
	virtual void EndCrash();
};