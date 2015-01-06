#include "stdafx.h"
#include "MapObject.h"
#include "GameManager.h"


MapObject::MapObject()
{
    m_UnitID = SET_MAIN_TYPE(MakeID(this), UNIT_OBSTRUCT);
}


MapObject::~MapObject()
{
}
