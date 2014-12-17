#include "pch.h"
#include "MoveRock.h"
#include "MapLayer.h"


MoveRock::MoveRock(int id, Vec2 pos)
{
    m_UnitID = id;

    m_Sprite = Sprite::create("Images/move_rock.png");
    m_Sprite->setPosition(pos);
    GET_MAP_LAYER->addChild(m_Sprite);
}


MoveRock::~MoveRock()
{
}
