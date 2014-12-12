#include "stdafx.h"
#include "ContactListener.h"
#include "GameManager.h"
#include "Unit.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

    auto lambda = [&](Unit* unit)
    {
        if (!unit || unit->GetUnitID() < 0)
        {
            printf(" - BeginContact Failed ! : unit is invalid \n");
            return;
        }
        unit->SetContectState(true);
        unit->Crashed();
    };
    lambda(unitA);
    lambda(unitB);
}

void ContactListener::EndContact(b2Contact* contact)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());

    auto lambda = [&](Unit* unit)
    {
        if (!unit || unit->GetUnitID() < 0)
        {
            printf(" - EndContact Failed ! : unit is invalid \n");
            return;
        }
        unit->Crashing(true);
        unit->SetContectState(false);
    };
    lambda(unitA);
    lambda(unitB);

    if (GGameManager->ApplyDamage(unitA, unitB))
    {
        GGameManager->ExchangeDamage(unitA, unitB);
    }
}