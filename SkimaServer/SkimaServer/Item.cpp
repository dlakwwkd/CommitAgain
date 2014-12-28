#include "stdafx.h"
#include "Item.h"
#include "Mob.h"
#include "Player.h"
#include "ClientSession.h"


Item::Item(Mob* mob, BuffTarget type)
{
    static int makeId = 0;
    m_UnitID = SET_MAIN_TYPE(++makeId, UNIT_ITEM);

    m_BuffType = type;

    SetStaticBody(mob->GetOwner(), ITEM_NORMAL, mob->GetBody()->GetPosition(), b2Vec2(30.0f, 30.0f));
    //m_Body->SetActive(false);

    auto client = m_Owner->GetClient();
    client->ItemBroadCast(m_Owner->GetPlayerID(), m_UnitID, m_Body->GetPosition(), true);
}


Item::~Item()
{
}

void Item::Dead()
{
    auto client = m_Owner->GetClient();
    client->ItemBroadCast(m_Owner->GetPlayerID(), m_UnitID, m_Body->GetPosition(), false);
}
