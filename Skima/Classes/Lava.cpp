#include "pch.h"
#include "Lava.h"
#include "MapLayer.h"


Lava::Lava(int id, Vec2 pos)
{
    m_UnitID = id;

    m_CenterSprite = Sprite::create("Images/lava_tile.png");
    m_CenterSprite->setScale(0.3f, 0.3f);
    m_CenterSprite->setPosition(pos);
    GET_MAP_LAYER->addChild(m_CenterSprite);
}


Lava::~Lava()
{
}
