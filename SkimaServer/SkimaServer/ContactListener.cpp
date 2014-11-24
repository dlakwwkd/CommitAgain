#include "stdafx.h"
#include "ContactListener.h"
#include "Unit.h"
#include "Hero.h"
#include "Missile.h"

void ContactListener::BeginContact(b2Contact *contact)
{
	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

	unitA->SetContectState(true);
	unitB->SetContectState(true);
	unitA->Crashed();
	unitB->Crashed();
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

	if (unitA->GetUnitType() == UNIT_MISSILE)
	{
		static_cast<Missile*>(unitA)->Extinction();
	}
	else
	{
		unitA->Crashing(true);
	}
	if (unitB->GetUnitType() == UNIT_MISSILE)
	{
		static_cast<Missile*>(unitB)->Extinction();
	}
	else
	{
		unitB->Crashing(true);
	}
	unitA->SetContectState(false);
	unitB->SetContectState(false);
}