#include "stdafx.h"
#include "FSM.h"
#include "Hero.h"
#include "GameManager.h"

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
	unit->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	unit->SetState(unit->GetStandbyState());

	if (unit->GetUnitType() == UNIT_MISSILE)
	{
		Crashed(unit);
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
	auto velocity = unit->GetBody()->GetLinearVelocity();
	velocity *= 0.2f;
	unit->GetBody()->SetLinearVelocity(velocity);
}

void CrashedState::EndMove(Unit* unit){}
void CrashedState::EndCrash(Unit* unit)
{
	unit->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
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
	if (!(abs(velocity.x) > 0.1f ||	abs(velocity.y) > 0.1f))
	{
		unit->Crashing(false);
	}

	if (unit->GetUnitType() == UNIT_MISSILE)
	{
		GGameManager->GetWolrd()->DestroyBody(unit->GetBody());
		unit->SetState(unit->GetStandbyState());
	}
}
