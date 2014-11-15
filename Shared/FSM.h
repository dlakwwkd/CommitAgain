#pragma once
class Hero;

class State
{
};
class MoveState : public State
{
public:
	virtual ~MoveState(){}
	virtual void TryMove(Hero* hero) = 0;
	virtual void Crashed(Hero* hero) = 0;
	virtual void EndMove(Hero* hero) = 0;
	virtual void EndCrash(Hero* hero) = 0;
	virtual void Movement(Hero* hero) = 0;
};
class StandbyState : public MoveState
{
public:
	virtual ~StandbyState(){}
	virtual void TryMove(Hero* hero);
	virtual void Crashed(Hero* hero);
	virtual void EndMove(Hero* hero);
	virtual void EndCrash(Hero* hero);
	virtual void Movement(Hero* hero);
};
class MovingState : public MoveState
{
public:
	virtual ~MovingState(){}
	virtual void TryMove(Hero* hero);
	virtual void Crashed(Hero* hero);
	virtual void EndMove(Hero* hero);
	virtual void EndCrash(Hero* hero);
	virtual void Movement(Hero* hero);
};
class CrashedState : public MoveState
{
public:
	virtual ~CrashedState(){}
	virtual void TryMove(Hero* hero);
	virtual void Crashed(Hero* hero);
	virtual void EndMove(Hero* hero);
	virtual void EndCrash(Hero* hero);
	virtual void Movement(Hero* hero);
};