﻿#include "stdafx.h"
#include "ContactListener.h"
#include "GameManager.h"
#include "Unit.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());
    if (!unitA->GetOwner() || !unitB->GetOwner())
    {
        printf(" - BeginContact Failed ! : unit is invalid \n");
        return;
    }
    unitA->SetContectState(true);
    unitB->SetContectState(true);
    unitA->Crashed();
    unitB->Crashed();

}

void ContactListener::EndContact(b2Contact* contact)
{
    auto unitA = static_cast<Unit*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto unitB = static_cast<Unit*>(contact->GetFixtureB()->GetBody()->GetUserData());
    if (!unitA->GetOwner() || !unitB->GetOwner())
    {
        printf(" - EndContact Failed ! : unit is invalid \n");
        return;
    }
    unitA->Crashing(true);
    unitB->Crashing(true);

    if (GGameManager->ApplyDamage(unitA, unitB))
    {
        GGameManager->ExchangeDamage(unitA, unitB);
    }
    //todo 나중에 미사일끼리 데미지 교환하여 미사일 없어지는것 구현해야함. 지금은 부딫히면 걍 없어짐

    unitA->SetContectState(false);
    unitB->SetContectState(false);
}