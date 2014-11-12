#include "stdafx.h"
#include "..\..\FSM.h"
#include "Unit.h"

//////////////////////////////////////////////////////////////////////////

	/*������*/

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

	/*�̵��� ����*/

//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Unit* unit){}
void MovingState::Crashed(Unit* unit)
{
	unit->SetState(unit->GetCrashedState());
	unit->GetBody()->SetLinearDamping(10.0f);

}

void MovingState::EndMove(Unit* unit)
{
	unit->SetState(unit->GetStandbyState());
	unit->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
}

void MovingState::EndCrash(Unit* unit){}
void MovingState::Movement(Unit* unit)
{
	unit->UnitMove();
}


//////////////////////////////////////////////////////////////////////////

	/*�з�������*/

//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove(Unit* unit){}
void CrashedState::Crashed(Unit* unit)
{
	//crash�Լ�
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
		unit->UnitCrashed(false);
		EndCrash(unit);
		printf(" - CrashEnd: UnitID:  %d, \t\t\t\t X : %.f\tY : %.f\n", unit->GetUnitID(),
			unit->GetBody()->GetPosition().x*PTM_RATIO, unit->GetBody()->GetPosition().y*PTM_RATIO);
	}
}