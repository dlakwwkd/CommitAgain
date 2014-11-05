#include "..\..\FSM.h"

//////////////////////////////////////////////////////////////////////////
/*
	대기 상태
*/
//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove()
{

}
void StandbyState::Stunned()
{

}
void StandbyState::Crashed()
{

}
void StandbyState::EndMove()
{

}
void StandbyState::EndStun()
{

}
void StandbyState::EndCrash()
{

}


//////////////////////////////////////////////////////////////////////////
/*
	이동 상태
*/
//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove()
{

}
void MovingState::Stunned()
{

}
void MovingState::Crashed()
{

}
void MovingState::EndMove()
{

}
void MovingState::EndStun()
{

}
void MovingState::EndCrash()
{

}


//////////////////////////////////////////////////////////////////////////
/*
	행동불가 상태
*/
//////////////////////////////////////////////////////////////////////////
void StunnedState::TryMove()
{

}
void StunnedState::Stunned()
{

}
void StunnedState::Crashed()
{

}
void StunnedState::EndMove()
{

}
void StunnedState::EndStun()
{

}
void StunnedState::EndCrash()
{

}

//////////////////////////////////////////////////////////////////////////
/*
	밀려남 상태
*/
//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove()
{

}
void CrashedState::Stunned()
{

}
void CrashedState::Crashed()
{

}
void CrashedState::EndMove()
{

}
void CrashedState::EndStun()
{

}
void CrashedState::EndCrash()
{

}

