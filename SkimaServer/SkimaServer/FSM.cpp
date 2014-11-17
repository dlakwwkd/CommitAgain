#include "stdafx.h"
#include "FSM.h"
#include "Hero.h"

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
	unit->GetBody()->SetLinearDamping(10.0f);
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
	unit->SetState(unit->GetCrashedState());
	unit->GetBody()->SetLinearDamping(10.0f);
}

void MovingState::EndMove(Unit* unit)
{
	unit->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	unit->SetState(unit->GetStandbyState());
}

void MovingState::EndCrash(Unit* unit){}
void MovingState::Movement(Unit* unit)
{
	unit->UnitMove();
}


//////////////////////////////////////////////////////////////////////////

	/*밀려남상태*/

//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove(Unit* unit){}
void CrashedState::Crashed(Unit* unit)
{
	auto velo = unit->GetBody()->GetLinearVelocity();
	velo.x /= 5;
	velo.y /= 5;
	unit->GetBody()->SetLinearVelocity(velo);
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
	if (!(abs(unit->GetBody()->GetLinearVelocity().x) > 0.1f ||
		abs(unit->GetBody()->GetLinearVelocity().y) > 0.1f))
	{
		EndCrash(unit);
		unit->Crashing(false);
		printf(" - CrashEnd: UnitID:  %d, \t\t\t\t X : %.f\tY : %.f\n", unit->GetUnitID(),
			unit->GetBody()->GetPosition().x*PTM_RATIO, unit->GetBody()->GetPosition().y*PTM_RATIO);
	}
}
