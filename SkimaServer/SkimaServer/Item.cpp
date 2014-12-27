#include "stdafx.h"
#include "Item.h"
#include "Mob.h"


Item::Item(Mob* mob, BuffTarget type)
{
    static int makeId = 0;
    m_UnitID = SET_MAIN_TYPE(++makeId, UNIT_ITEM);

    m_BuffType = type;

    SetDynamicBody(mob->GetOwner(), ITEM_NORMAL, mob->GetBody()->GetPosition(), 30.0f);
}


Item::~Item()
{
}
