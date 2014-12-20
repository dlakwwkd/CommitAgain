#include "pch.h"
#include "Lava.h"
#include "MapLayer.h"


Lava::Lava(int id, Vec2 pos)
{
    m_UnitID = id;

    m_Sprite = Sprite::create("Images/lava_tile.png");
    m_Sprite->setScale(0.3f, 0.3f);
    m_Sprite->setPosition(pos);
    GET_MAP_LAYER->addChild(m_Sprite);
}


Lava::~Lava()
{
}
