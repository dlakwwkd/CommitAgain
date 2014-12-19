#include "stdafx.h"
#include "MapObject.h"
#include "GameManager.h"


MapObject::MapObject()
{
	static int makeId = 0;
	m_UnitID = SET_MAIN_TYPE(++makeId, UNIT_OBSTRUCT);
    m_Hp = 0;
}


MapObject::~MapObject()
{
}
