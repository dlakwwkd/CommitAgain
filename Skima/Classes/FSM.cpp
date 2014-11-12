#include "pch.h"
#include "../../FSM.h"
#include "Unit.h"

//////////////////////////////////////////////////////////////////////////
/*
	대기 상태
*/
//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove(Unit* unit)
{
	unit->SetMoveState(unit->GetMovingState());

	auto distance = unit->GetMoveTargetPos() - unit->GetSprite()->getPosition();
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 300;
	auto action1 = MoveTo::create(scala, unit->GetMoveTargetPos());
	auto action2 = CallFunc::create(CC_CALLBACK_0(Unit::EndMove, unit));
	auto action3 = Sequence::create(action1, action2, NULL);
	unit->GetSprite()->runAction(action3);
}

void StandbyState::Crashed(Unit* unit)
{
	unit->SetMoveState(unit->GetCrashedState());

	auto distance = unit->GetMoveTargetPos() - unit->GetSprite()->getPosition();
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 200;
	auto action1 = MoveTo::create(scala, unit->GetMoveTargetPos());
	auto action2 = EaseSineOut::create(action1);
	unit->GetSprite()->runAction(action2);
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

	auto distance = unit->GetMoveTargetPos() - unit->GetSprite()->getPosition();
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 300;
	auto action1 = MoveTo::create(scala, unit->GetMoveTargetPos());
	auto action2 = CallFunc::create(CC_CALLBACK_0(Unit::EndMove, unit));
	auto action3 = Sequence::create(action1, action2, NULL);
	unit->GetSprite()->runAction(action3);
}
void MovingState::Crashed(Unit* unit)
{
	unit->SetMoveState(unit->GetCrashedState());
	unit->GetSprite()->stopAllActions();

	auto distance = unit->GetMoveTargetPos() - unit->GetSprite()->getPosition();
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 200;
	auto action1 = MoveTo::create(scala, unit->GetMoveTargetPos());
	auto action2 = EaseSineOut::create(action1);
	unit->GetSprite()->runAction(action2);
}

void MovingState::EndMove(Unit* unit)
{
	unit->SetMoveState(unit->GetStandbyState());
}

void MovingState::EndCrash(Unit* unit){}
void MovingState::Movement(Unit* unit)
{
	//unit->Move();
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
}

void CrashedState::Movement(Unit* unit)
{
	//unit->Crash();
}

