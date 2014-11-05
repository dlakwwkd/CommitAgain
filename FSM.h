#pragma once

<<<<<<< HEAD
=======
class Unit;

>>>>>>> origin/Client_v0.2
class State
{
};

class MoveState : public State
{
public:
<<<<<<< HEAD
	virtual void TryMove()	= 0;
	virtual void Stunned()	= 0;
	virtual void Crashed()	= 0;

	virtual void EndMove()	= 0;
	virtual void EndStun()	= 0;
	virtual void EndCrash() = 0;
=======
	virtual void TryMove(Unit* unit) = 0;
	virtual void Crashed(Unit* unit) = 0;
	virtual void EndMove(Unit* unit) = 0;
	virtual void EndCrash(Unit* unit) = 0;
>>>>>>> origin/Client_v0.2
};

class StandbyState : public MoveState
{
public:
<<<<<<< HEAD
	virtual void TryMove();
	virtual void Stunned();
	virtual void Crashed();

	virtual void EndMove();
	virtual void EndStun();
	virtual void EndCrash();
=======
	virtual void TryMove(Unit* unit);
	virtual void Crashed(Unit* unit);
	virtual void EndMove(Unit* unit);
	virtual void EndCrash(Unit* unit);
>>>>>>> origin/Client_v0.2
};
class MovingState : public MoveState
{
public:
<<<<<<< HEAD
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
=======
	virtual void TryMove(Unit* unit);
	virtual void Crashed(Unit* unit);
	virtual void EndMove(Unit* unit);
	virtual void EndCrash(Unit* unit);
>>>>>>> origin/Client_v0.2
};
class CrashedState : public MoveState
{
public:
<<<<<<< HEAD
	virtual void TryMove();
	virtual void Stunned();
	virtual void Crashed();

	virtual void EndMove();
	virtual void EndStun();
	virtual void EndCrash();
=======
	virtual void TryMove(Unit* unit);
	virtual void Crashed(Unit* unit);
	virtual void EndMove(Unit* unit);
	virtual void EndCrash(Unit* unit);
>>>>>>> origin/Client_v0.2
};