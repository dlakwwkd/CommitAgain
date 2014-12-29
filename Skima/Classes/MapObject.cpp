#include "pch.h"
#include "MapObject.h"
#include "RockEffect.h"
#include "ObjectLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

MapObject::MapObject()
{
    m_UnitType = UNIT_OBSTRUCT;
}


MapObject::~MapObject()
{
}

void MapObject::MapObjectBreak()
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/rockcrash");
    RockEffect* effect = new RockEffect();
    effect->CreateEffect(m_CenterSprite->getPosition());
    GET_OBJECT_LAYER->removeChild(m_CenterSprite);
}
