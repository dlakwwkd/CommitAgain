#include "pch.h"
#include "Lava.h"


Lava::Lava(int id, Vec2 pos)
{
    m_UnitID = id;

    m_CenterSprite = Sprite::create("Images/Unit/lava_tile.png");
    m_CenterSprite->setScale(0.3f, 0.3f);
    m_CenterSprite->setPosition(pos);
}


Lava::~Lava()
{
}
