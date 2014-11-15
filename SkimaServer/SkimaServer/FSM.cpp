#include "stdafx.h"
#include "FSM.h"
#include "Hero.h"

//////////////////////////////////////////////////////////////////////////

	/*대기상태*/

//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove(Hero* hero)
{
	hero->SetState(hero->GetMovingState());
}

void StandbyState::Crashed(Hero* hero)
{
	hero->SetState(hero->GetCrashedState());
	hero->GetBody()->SetLinearDamping(10.0f);
}

void StandbyState::EndMove(Hero* hero){}
void StandbyState::EndCrash(Hero* hero){}
void StandbyState::Movement(Hero* hero){}


//////////////////////////////////////////////////////////////////////////

	/*이동중 상태*/

//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Hero* hero){}
void MovingState::Crashed(Hero* hero)
{
	hero->SetState(hero->GetCrashedState());
	hero->GetBody()->SetLinearDamping(10.0f);
}

void MovingState::EndMove(Hero* hero)
{
	hero->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	hero->SetState(hero->GetStandbyState());
}

void MovingState::EndCrash(Hero* hero){}
void MovingState::Movement(Hero* hero)
{
	hero->HeroMove();
}


//////////////////////////////////////////////////////////////////////////

	/*밀려남상태*/

//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove(Hero* hero){}
void CrashedState::Crashed(Hero* hero)
{
	auto velo = hero->GetBody()->GetLinearVelocity();
	velo.x /= 5;
	velo.y /= 5;
	hero->GetBody()->SetLinearVelocity(velo);
}

void CrashedState::EndMove(Hero* hero){}
void CrashedState::EndCrash(Hero* hero)
{
	hero->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	hero->GetBody()->SetLinearDamping(0.0f);
	hero->SetState(hero->GetStandbyState());
}

void CrashedState::Movement(Hero* hero)
{
	if (!(abs(hero->GetBody()->GetLinearVelocity().x) > 0.1f ||
		abs(hero->GetBody()->GetLinearVelocity().y) > 0.1f))
	{
		EndCrash(hero);
		hero->HeroCrashed(false);
		printf(" - CrashEnd: UnitID:  %d, \t\t\t\t X : %.f\tY : %.f\n", hero->GetUnitID(),
			hero->GetBody()->GetPosition().x*PTM_RATIO, hero->GetBody()->GetPosition().y*PTM_RATIO);
	}
}
