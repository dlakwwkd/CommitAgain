#include "stdafx.h"
#include "ContactListener.h"
#include "GameManager.h"
#include "Unit.h"

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (unitA && unitA->GetUnitID() > 0)
    {
        unitA->Crashing();
    }
    if (unitB && unitB->GetUnitID() > 0)
    {
        unitB->Crashing();
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

    int damageAble = 0;
    if (unitA && unitA->GetUnitID() > 0)
    {
        unitA->Crashed(unitB);
        ++damageAble;
    }
    if (unitB && unitB->GetUnitID() > 0)
    {
        unitB->Crashed(unitA);
        ++damageAble;
    }
    if (damageAble == 2)
    {
        GGameManager->CrashDamage(unitA, unitB);
    }
}