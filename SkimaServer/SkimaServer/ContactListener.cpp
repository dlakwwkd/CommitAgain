#include "stdafx.h"
#include "ContactListener.h"
#include "GameManager.h"
#include "Unit.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if (unitA && unitA->GetUnitID() > 0)
    {
        unitA->SetContectState(true);
        unitA->Crashed();
    }
    if (unitB && unitB->GetUnitID() > 0)
    {
        unitB->SetContectState(true);
        unitB->Crashed();
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

    int damageAble = 0;
    if (unitA && unitA->GetUnitID() > 0)
    {
        unitA->Crashing();
        unitA->SetContectState(false);
        ++damageAble;
    }
    if (unitB && unitB->GetUnitID() > 0)
    {
        unitB->Crashing();
        unitB->SetContectState(false);
        ++damageAble;
    }
    if (damageAble == 2)
    {
        GGameManager->CrashDamage(unitA, unitB);
    }
}