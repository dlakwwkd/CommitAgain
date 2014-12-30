#include "pch.h"
#include "MoveRock.h"


MoveRock::MoveRock(int id, Vec2 pos)
{
    m_UnitID = id;

    m_CenterSprite = Sprite::create("Images/Unit/move_rock.png");
    m_CenterSprite->setPosition(pos);
}


MoveRock::~MoveRock()
{
}

void MoveRock::SetMoveMotionToCache()
{

}

void MoveRock::SetMoveMotionByDir()
{

}
