#include "stdafx.h"
#include "FSM.h"
#include "Hero.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Missile.h"

//////////////////////////////////////////////////////////////////////////

    /*대기상태*/

//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove(Unit* unit)
{
    unit->SetState(unit->GetMovingState());
}

void StandbyState::Crashed(Unit* unit)
{
    unit->GetBody()->SetLinearDamping(DAMPING);
    unit->SetState(unit->GetCrashedState());
}

void StandbyState::EndMove(Unit* unit){}
void StandbyState::EndCrash(Unit* unit){}
void StandbyState::Movement(Unit* unit){}


//////////////////////////////////////////////////////////////////////////

    /*이동중 상태*/

//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Unit* unit){}
void MovingState::Crashed(Unit* unit)
{
    unit->GetBody()->SetLinearDamping(DAMPING);
    unit->SetState(unit->GetCrashedState());
}

void MovingState::EndMove(Unit* unit)
{
    unit->GetBody()->SetAwake(false);
    unit->SetState(unit->GetStandbyState());

    switch (GET_MAIN_TYPE(unit->GetUnitID()))
    {
    case UNIT_MISSILE:
        Crashed(unit);
        break;
    }
}

void MovingState::EndCrash(Unit* unit){}
void MovingState::Movement(Unit* unit)
{
    unit->Moving();
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
        unit->Crashing(false);
    }
}

//////////////////////////////////////////////////////////////////////////

    /*스킬시전 상태*/

//////////////////////////////////////////////////////////////////////////
void UseSkillState::TryMove(Unit* unit)
{

}

void UseSkillState::Crashed(Unit* unit)
{

}

void UseSkillState::EndMove(Unit* unit)
{

}

void UseSkillState::EndCrash(Unit* unit)
{

}

void UseSkillState::Movement(Unit* unit)
{

}
