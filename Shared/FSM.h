#pragma once
class Unit;

class State
{
};


///# FSM을 만드려면, 현재 state에 대한 정보를 담고 있는 멤버 변수가 반드시 있어야 한다. 그냥 아래처럼 함수만 있으면 굳이 아래처럼 할 필요도 없음.
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

///# FSM을 어떻게 만드는지는 선배들의 프로젝트를 참고하라
/// 액션에 대한 FSM 예
// https://github.com/NHNNEXT/2014-01-HUDIGAME-EunJaRim/blob/master/YaMang/YaMangServer/YaMangServer/Action.h

