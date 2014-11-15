#include "stdafx.h"
#include "ContactListener.h"
#include "Unit.h"
#include "Hero.h"

void ContactListener::BeginContact(b2Contact *contact)
{
	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

	UnitType unitType = unitA->GetUnitType();
	
	switch (unitType)
	{
	case UNIT_HERO:
		Hero* hero = dynamic_cast<Hero*>(unitA);
		hero->Crashed();
		break;

	case UNIT_MISSILE:
		Missile* missile = dynamic_cast<Missile*>(unitA);
		hero->Crashed();
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

	unitA->HeroCrashed(true);
	unitB->HeroCrashed(true);
}
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
