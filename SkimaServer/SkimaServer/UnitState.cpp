#include "stdafx.h"
#include "Unit.h"
#include "..\..\FSM.h"

//////////////////////////////////////////////////////////////////////////

	/*대기상태*/

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
	//없음
}

void StandbyState::EndCrash(Unit* unit)
{
	//없음
}
//////////////////////////////////////////////////////////////////////////

	/*이동중 상태*/

//////////////////////////////////////////////////////////////////////////

void MovingState::TryMove(Unit* unit)
{
	unit->UnitMove();
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
	//없음
}


//////////////////////////////////////////////////////////////////////////

	/*밀려남상태*/

//////////////////////////////////////////////////////////////////////////

void CrashedState::TryMove(Unit* unit)
{
	//없음
}

void CrashedState::Crashed(Unit* unit)
{
	//crash함수
}

void CrashedState::EndMove(Unit* unit)
{
	//없음
}

void CrashedState::EndCrash(Unit* unit)
{
	unit->SetState(unit->GetStandbyState());
}
