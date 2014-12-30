#include "pch.h"
#include "Rock.h"


Rock::Rock(int id, Vec2 pos)
{
    m_UnitID = id;

    m_CenterSprite = Sprite::create("Images/Unit/rock.png");
    m_CenterSprite->setPosition(pos);
}


Rock::~Rock()
{
}

void Rock::SetMoveMotionToCache()
{

}

void Rock::SetMoveMotionByDir()
{

}
