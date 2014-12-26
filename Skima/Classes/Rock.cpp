#include "pch.h"
#include "Rock.h"
#include "MapLayer.h"

Rock::Rock(int id, Vec2 pos)
{
    m_UnitID = id;

    m_CenterSprite = Sprite::create("Images/rock.png");
    m_CenterSprite->setPosition(pos);
    GET_MAP_LAYER->addChild(m_CenterSprite);
}


Rock::~Rock()
{
}
