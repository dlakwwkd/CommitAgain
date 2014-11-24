#include "stdafx.h"
#include "ContactListener.h"
#include "Unit.h"
#include "Hero.h"
#include "Missile.h"
#include "GameManager.h"

void ContactListener::BeginContact(b2Contact *contact)
{
	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (unitA->GetPlayerID() < 0 || unitB->GetPlayerID() < 0)
	{
		printf(" - BeginContact Failed ! : unit is invalid \n");
		return;
	}

	unitA->SetContectState(true);
	unitB->SetContectState(true);
	unitA->Crashed();
	unitB->Crashed();

	if (GGameManager->ApplyDamage(unitA,unitB))
		GGameManager->ExchangeDamage(unitA, unitB);
	
	//EndContact()와 관련해서 body같은거 제거해도 될지는 테스트해봐야함
	if (unitA->GetUnitHp() <= 0)
		unitA->IamDead();
	if (unitB->GetUnitHp() <= 0)
		unitB->IamDead();
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
// 	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
// 	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());
// 
// 	unitA->Crashing(true);
// 	unitB->Crashing(true);
}

void ContactListener::EndContact(b2Contact* contact)
{
	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if (unitA->GetPlayerID() < 0 || unitB->GetPlayerID() < 0)
	{
		printf(" - EndContact Failed ! : unit is invalid \n");
		return;
	}

	unitA->Crashing(true);
	unitB->Crashing(true);

	if (unitA->GetUnitType() == UNIT_MISSILE)
	{
		static_cast<Missile*>(unitA)->Extinction();
	}
	if (unitB->GetUnitType() == UNIT_MISSILE)
	{
		static_cast<Missile*>(unitB)->Extinction();
	}

	unitA->SetContectState(false);
	unitB->SetContectState(false);
}