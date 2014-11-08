#include "../../FSM.h"
#include "Unit.h"

//////////////////////////////////////////////////////////////////////////
/*
	대기 상태
*/
//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove(Unit* unit)
{
	unit->SetState(unit->GetMovingState());
}
void StandbyState::Crashed(Unit* unit)
{
	unit->SetState(unit->GetCrashedState());
}
void StandbyState::EndMove(Unit* unit)
{

}
void StandbyState::EndCrash(Unit* unit)
{

}
void StandbyState::Movement(Unit* unit)
{

}

//////////////////////////////////////////////////////////////////////////
/*
	이동 상태
*/
//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Unit* unit)
{

}
void MovingState::Crashed(Unit* unit)
{
	unit->SetState(unit->GetCrashedState());

}
void MovingState::EndMove(Unit* unit)
{
	unit->SetState(unit->GetStandbyState());
}
void MovingState::EndCrash(Unit* unit)
{

}
void MovingState::Movement(Unit* unit)
{
	unit->Move();
}


//////////////////////////////////////////////////////////////////////////
/*
	밀려남 상태
*/
//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove(Unit* unit)
{

}
void CrashedState::Crashed(Unit* unit)
{

}
void CrashedState::EndMove(Unit* unit)
{

}
void CrashedState::EndCrash(Unit* unit)
{
	unit->SetState(unit->GetStandbyState());
}
void CrashedState::Movement(Unit* unit)
{

}

