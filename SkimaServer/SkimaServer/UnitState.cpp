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

void StandbyState::Movement(Unit* unit)
{

}

void StandbyState::Crashed(Unit* unit)
{
	unit->SetState(unit->GetCrashedState());
	unit->GetBody()->SetLinearDamping(3.0f);
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
	
}

void MovingState::Movement(Unit* unit)
{
	unit->UnitMove();
}

void MovingState::Crashed(Unit* unit)
{
	unit->SetState(unit->GetCrashedState());
	unit->GetBody()->SetLinearDamping(3.0f);
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

void CrashedState::Movement(Unit* unit)
{
	if (!(abs(unit->GetBody()->GetLinearVelocity().x) > 0.1 ||
		abs(unit->GetBody()->GetLinearVelocity().y) > 0.1))
	{
		unit->UnitCrashed(false);
		EndCrash(unit);
	}
	else
	{
		unit->UnitCrashed(true); ///# 이 부분이 너무 많이 호출됨..
	}
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
	unit->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	unit->GetBody()->SetLinearDamping(0.0f);
}
