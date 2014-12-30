#include "pch.h"
#include "MapLayer.h"


bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto sprite = Sprite::create("Images/Background/bg2.png");
    sprite->setPosition(this->getAnchorPointInPoints());
    this->addChild(sprite);
    return true;
}

void MapLayer::MakeObject(int id, Vec2 pos)
{
    //id로 타입 구별 먼저 해줘야 함

//     auto rock = Sprite::create("Images/rock.png");
//     rock->setPosition(pos);
//     this->addChild(rock);
// 
//     return;
}
