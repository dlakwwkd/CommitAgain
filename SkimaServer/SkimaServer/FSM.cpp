#include "stdafx.h"
#include "FSM.h"
#include "Unit.h"
#include "Player.h"

//////////////////////////////////////////////////////////////////////////

    /*대기상태*/

//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove(Unit* unit)
{
    unit->SetState(unit->GetMovingState());
    unit->Moving();
}

void StandbyState::Crashed(Unit* unit)
{
    unit->GetBody()->SetLinearDamping(DAMPING);
    unit->SetState(unit->GetCrashedState());
    unit->SetUnitHiddenState(false);
}

void StandbyState::EndMove(Unit* unit){}
void StandbyState::EndCrash(Unit* unit){}
void StandbyState::Movement(Unit* unit){}


//////////////////////////////////////////////////////////////////////////

    /*이동중 상태*/

//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Unit* unit)
{
    unit->Moving();
}

void MovingState::Crashed(Unit* unit)
{
    unit->GetBody()->SetLinearDamping(DAMPING);
    unit->SetState(unit->GetCrashedState());
    unit->SetUnitHiddenState(false);
}

void MovingState::EndMove(Unit* unit)
{
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_MISSILE)
    {
        unit->Crashed();
        unit->Crashing();
        return;
    }
    unit->GetBody()->SetAwake(false);
    unit->SetState(unit->GetStandbyState());
}

void MovingState::EndCrash(Unit* unit){}
void MovingState::Movement(Unit* unit)
{
    unit->ReachCheck();
}


//////////////////////////////////////////////////////////////////////////

    /*밀려남상태*/

//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove(Unit* unit){}
void CrashedState::Crashed(Unit* unit)
{
}

void CrashedState::EndMove(Unit* unit){}
void CrashedState::EndCrash(Unit* unit)
{
    unit->CurPosSync();
    unit->GetBody()->SetAwake(false);
    unit->GetBody()->SetLinearDamping(0.0f);
    unit->SetState(unit->GetStandbyState());
}

void CrashedState::Movement(Unit* unit)
{
    if (unit->GetContectState() == true)
    {
        return;
    }
    auto velocity = unit->GetBody()->GetLinearVelocity();
    if (velocity.Length() < 0.5f)
    {
        unit->EndCrash();
    }
}
