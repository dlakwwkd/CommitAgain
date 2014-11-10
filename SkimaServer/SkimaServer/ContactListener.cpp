#include "stdafx.h"
#include "ContactListener.h"
#include "Unit.h"


ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact *contact)
{
	auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
	auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

	unitA->Crashed();
	unitB->Crashed();
}

void ContactListener::EndContact(b2Contact* contact)
{

}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}
