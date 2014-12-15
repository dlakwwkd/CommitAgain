#include "pch.h"
#include "FSM.h"
#include "Unit.h"

//////////////////////////////////////////////////////////////////////////
/*
    대기 상태
*/
//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetMovingState());
    unit->Move();
}

void StandbyState::Crashed(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetCrashedState());
    unit->GetSprite()->stopAllActions();
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
    }
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_OBSTRUCT)
    {
        CCLOG("OBSTRUCT CRASH");
    }
    unit->Crash();
}

void StandbyState::EndMove(Unit* unit){}
void StandbyState::EndCrash(Unit* unit)
{
    if (unit == nullptr) return;
    auto action1 = MoveTo::create(1.0f, unit->GetMoveTargetPos());
    auto action2 = EaseSineIn::create(action1);
    unit->GetSprite()->runAction(action2);
}
void StandbyState::Movement(Unit* unit){}


//////////////////////////////////////////////////////////////////////////
/*
    이동 상태
*/
//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Unit* unit)
{
    if (unit == nullptr) return;
    unit->GetSprite()->stopAllActions();
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
    }
    unit->Move();
}

void MovingState::Crashed(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetCrashedState());
    unit->GetSprite()->stopAllActions();
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
    }
    unit->Crash();
}

void MovingState::EndMove(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetStandbyState());
    unit->GetSprite()->stopAllActions();
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
    }
}

void MovingState::EndCrash(Unit* unit){}
void MovingState::Movement(Unit* unit)
{
}


//////////////////////////////////////////////////////////////////////////
/*
    밀려남 상태
*/
//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove(Unit* unit){}
void CrashedState::Crashed(Unit* unit)
{
    if (unit == nullptr) return;
    unit->GetSprite()->stopAllActions();
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
    }
    unit->Crash();
}
void CrashedState::EndMove(Unit* unit){}
void CrashedState::EndCrash(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetStandbyState());
    unit->GetSprite()->stopAllActions();
    if(GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
    }

    auto action1 = MoveTo::create(0.1f, unit->GetMoveTargetPos());
    auto action2 = EaseSineIn::create(action1);
    unit->GetSprite()->runAction(action2);
}
void CrashedState::Movement(Unit* unit)
{
}
