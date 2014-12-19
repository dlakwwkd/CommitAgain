#include "pch.h"
#include "MapObject.h"
#include "RockEffect.h"
#include "MapLayer.h"


MapObject::MapObject()
{
    m_UnitType = UNIT_OBSTRUCT;
}


MapObject::~MapObject()
{
}

void MapObject::MapObjectBreak()
{
    RockEffect* effect = new RockEffect();
    effect->CreateEffect(m_Sprite->getPosition());
    GET_MAP_LAYER->removeChild(m_Sprite);
}
