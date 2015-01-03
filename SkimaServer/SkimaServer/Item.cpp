#include "stdafx.h"
#include "Item.h"
#include "Mob.h"
#include "Player.h"
#include "ClientSession.h"
#include "Game.h"
#include "GameManager.h"
#include "Timer.h"

Item::Item(Mob* mob, BuffTarget buffType)
{
    m_UnitID = SET_MAIN_TYPE(MakeID(this), UNIT_ITEM);

    m_BuffType = buffType;

    SetDynamicBody(mob->GetOwner(), ITEM_NORMAL, mob->GetBody()->GetPosition(), 30.0f);
    m_Body->SetActive(false);

    auto pos = m_Body->GetPosition();
    auto scale = Reduce(30.0f);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&GameManager::FieldCheck, GGameManager, this, pos, scale);
    m_Timer = new Timer(m_Owner->GetRoomID());
    m_Timer->InfiniteTimer(200, func);
    game->PushTimer(m_Timer);

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
