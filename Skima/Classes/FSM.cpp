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
	unit->SetMoveState(unit->GetMovingState());
	unit->Move();
}

void StandbyState::Crashed(Unit* unit)
{
	unit->SetMoveState(unit->GetCrashedState());
	unit->Crash();
	unit->UpdateHpBar();
}

void StandbyState::EndMove(Unit* unit){}
void StandbyState::EndCrash(Unit* unit){}
void StandbyState::Movement(Unit* unit){}


//////////////////////////////////////////////////////////////////////////
/*
	이동 상태
*/
//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Unit* unit)
{
	unit->GetSprite()->stopAllActions();
	unit->Move();

}
void MovingState::Crashed(Unit* unit)
{
	unit->SetMoveState(unit->GetCrashedState());
	unit->GetSprite()->stopAllActions();
	unit->Crash();
	unit->UpdateHpBar();
}

void MovingState::EndMove(Unit* unit)
{
	unit->SetMoveState(unit->GetStandbyState());
	unit->GetSprite()->stopAllActions();
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
void CrashedState::Crashed(Unit* unit){}
void CrashedState::EndMove(Unit* unit){}
void CrashedState::EndCrash(Unit* unit)
{
	unit->SetMoveState(unit->GetStandbyState());
	unit->GetSprite()->stopAllActions();

	auto action1 = MoveTo::create(0.1f, unit->GetMoveTargetPos());
	auto action2 = EaseSineIn::create(action1);
	unit->GetSprite()->runAction(action2);
}

void CrashedState::Movement(Unit* unit)
{
}

