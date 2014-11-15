#include "stdafx.h"
#include "ContactListener.h"
#include "Unit.h"
#include "Hero.h"
#include "Missile.h"

void ContactListener::BeginContact(b2Contact *contact)
{
	Unit* crashUnit[2];

	crashUnit[0] = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	crashUnit[1]= static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

	for (int i = 0; i < _countof(crashUnit); ++i)
	{
		crashUnit[i]->BeginCrashed();
	}

}

void ContactListener::EndContact(b2Contact* contact)
{
	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

	unitA->Crashing(true);
	unitB->Crashing(true);
}
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
