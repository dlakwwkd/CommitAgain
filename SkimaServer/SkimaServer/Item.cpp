#include "stdafx.h"
#include "Item.h"
#include "Mob.h"
#include "Player.h"
#include "ClientSession.h"
#include "Game.h"
#include "Timer.h"

Item::Item(Mob* mob, BuffTarget buffType)
{
    m_UnitID = SET_MAIN_TYPE(MakeID(this), UNIT_ITEM);

    m_BuffType = buffType;

    SetDynamicBody(mob->GetOwner(), ITEM_NORMAL, mob->GetBody()->GetPosition(), 50.0f);
    m_Body->SetActive(false);

    auto pos = m_Body->GetPosition();
    auto scale = Reduce(50.0f);
    m_TakeRange.m_Top = pos.y + scale;
    m_TakeRange.m_Bottom = pos.y - scale;
    m_TakeRange.m_Left = pos.x - scale;
    m_TakeRange.m_Right = pos.x + scale;

    auto game = m_Owner->GetGame();
    m_Timer = Timer::Push(game, 200, TIMER_INFINITE, GGameManager, &GameManager::FieldCheck, this);

    auto client = m_Owner->GetClient();
    client->ItemBroadCast(m_Owner->GetPlayerID(), m_UnitID, m_Body->GetPosition(), true, m_BuffType);
}


Item::~Item()
{
    if (m_Timer)
    {
        m_Timer->SetOff();
    }
}

void Item::Dead()
{
    auto client = m_Owner->GetClient();
    client->ItemBroadCast(m_Owner->GetPlayerID(), m_UnitID, m_Body->GetPosition(), false, m_BuffType);
}
