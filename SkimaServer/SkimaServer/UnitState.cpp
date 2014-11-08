#include "stdafx.h"
#include "Unit.h"
#include "..\..\FSM.h"

//////////////////////////////////////////////////////////////////////////

	/*������*/

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
}

void StandbyState::EndMove(Unit* unit)
{
	//����
}

void StandbyState::EndCrash(Unit* unit)
{
	//����
}
//////////////////////////////////////////////////////////////////////////

	/*�̵��� ����*/

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
}

void MovingState::EndMove(Unit* unit)
{
	unit->SetState(unit->GetStandbyState());
}

void MovingState::EndCrash(Unit* unit)
{
	//����
}


//////////////////////////////////////////////////////////////////////////

	/*�з�������*/

//////////////////////////////////////////////////////////////////////////

void CrashedState::TryMove(Unit* unit)
{
	//����
}

void CrashedState::Movement(Unit* unit)
{
	if (unit->GetBody()->GetLinearVelocity() == b2Vec2(0, 0))
	{
		unit->UnitCrashed(false);
		EndCrash(unit);
	}
	else
	{
		unit->UnitCrashed(true);
	}
}

void CrashedState::Crashed(Unit* unit)
{
	//crash�Լ�
}

void CrashedState::EndMove(Unit* unit)
{
	//����
}

void CrashedState::EndCrash(Unit* unit)
{
	unit->SetState(unit->GetStandbyState());
}
