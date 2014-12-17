#include "pch.h"
#include "MapObject.h"
#include "RockEffect.h"


MapObject::MapObject()
{

}


MapObject::~MapObject()
{
}

void MapObject::MapObjectBreak()
{
    RockEffect* effect;
    effect->CreateEffect(m_Sprite->getPosition());
}
