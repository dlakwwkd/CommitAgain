#include "pch.h"
#include "FSM.h"
#include "Unit.h"

//////////////////////////////////////////////////////////////////////////
/*
    대기 상태
*/
//////////////////////////////////////////////////////////////////////////
void StandbyState::TryMove(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetMovingState());
    unit->Move();
}

void StandbyState::Crashed(Unit* unit)
{
    if (unit == nullptr) return;
    if (unit->GetUnitType() == UNIT_HERO)
    {
        unit->SetAllSpriteVisible();
        unit->SetUnitHiddenState(false);
    }
    unit->SetMoveState(unit->GetCrashedState());
    unit->GetCenterSprite()->stopAllActions();
    unit->GetCenterSprite()->setVisible(true);
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
        unit->GetRealSprite()->setVisible(true);
    }
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_OBSTRUCT)
    {
        CCLOG("OBSTRUCT CRASH");
    }
    unit->Crash();
}

void StandbyState::EndMove(Unit* unit){}
void StandbyState::EndCrash(Unit* unit)
{
    if (unit == nullptr) return;
    auto action1 = MoveTo::create(1.0f, unit->GetTargetPos());
    auto action2 = EaseSineIn::create(action1);
    unit->GetCenterSprite()->runAction(action2);
}
void StandbyState::Movement(Unit* unit){}


//////////////////////////////////////////////////////////////////////////
/*
    이동 상태
*/
//////////////////////////////////////////////////////////////////////////
void MovingState::TryMove(Unit* unit)
{
    if (unit == nullptr) return;
    unit->GetCenterSprite()->stopAllActions();
    unit->GetCenterSprite()->setVisible(true);
    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
        unit->GetRealSprite()->setVisible(true);

    }
    unit->Move();
}

void MovingState::Crashed(Unit* unit)
{
    if (unit == nullptr) return;
    if (unit->GetUnitType() == UNIT_HERO)
    {
        unit->SetAllSpriteVisible();
        unit->SetUnitHiddenState(false);
    }
    unit->SetMoveState(unit->GetCrashedState());
    unit->GetCenterSprite()->stopAllActions();
    unit->GetCenterSprite()->setVisible(true);

    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
        unit->GetRealSprite()->setVisible(true);
    }
    unit->Crash();
}

void MovingState::EndMove(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetStandbyState());
    unit->GetCenterSprite()->stopAllActions();
    unit->GetCenterSprite()->setVisible(true);

    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
        unit->GetRealSprite()->setVisible(true);
    }
}

void MovingState::EndCrash(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetStandbyState());
    unit->GetCenterSprite()->stopAllActions();
    unit->GetCenterSprite()->setVisible(true);

    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
        unit->GetRealSprite()->setVisible(true);
    }
    auto action1 = MoveTo::create(0.1f, unit->GetTargetPos());
    auto action2 = EaseSineIn::create(action1);
    unit->GetCenterSprite()->runAction(action2);
}
void MovingState::Movement(Unit* unit)
{
}


//////////////////////////////////////////////////////////////////////////
/*
    밀려남 상태
*/
//////////////////////////////////////////////////////////////////////////
void CrashedState::TryMove(Unit* unit){}
void CrashedState::Crashed(Unit* unit)
{
    if (unit == nullptr) return;
    if (unit->GetUnitType() == UNIT_HERO)
    {
        unit->SetAllSpriteVisible();
        unit->SetUnitHiddenState(false);
    }
    unit->GetCenterSprite()->stopAllActions();
    unit->GetCenterSprite()->setVisible(true);

    if (GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
        unit->GetRealSprite()->setVisible(true);
    }
    unit->Crash();
}
void CrashedState::EndMove(Unit* unit){}
void CrashedState::EndCrash(Unit* unit)
{
    if (unit == nullptr) return;
    unit->SetMoveState(unit->GetStandbyState());
    unit->GetCenterSprite()->stopAllActions();
    unit->GetCenterSprite()->setVisible(true);

    if(GET_MAIN_TYPE(unit->GetUnitID()) == UNIT_HERO)
    {
        unit->GetRealSprite()->stopAllActions();
        unit->GetRealSprite()->setVisible(true);
    }

    auto action1 = MoveTo::create(0.1f, unit->GetTargetPos());
    auto action2 = EaseSineIn::create(action1);
    unit->GetCenterSprite()->runAction(action2);
}
void CrashedState::Movement(Unit* unit)
{
}
