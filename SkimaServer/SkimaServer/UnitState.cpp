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
	unit->GetBody()->SetLinearDamping(3.0f);
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
	unit->GetBody()->SetLinearDamping(3.0f);
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
	if (!(abs(unit->GetBody()->GetLinearVelocity().x) > 0.1 ||
		abs(unit->GetBody()->GetLinearVelocity().y) > 0.1))
	{
		unit->UnitCrashed(false);
		EndCrash(unit);
	}
	else
	{
		unit->UnitCrashed(true); ///# �� �κ��� �ʹ� ���� ȣ���..
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
	unit->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	unit->GetBody()->SetLinearDamping(0.0f);
}
