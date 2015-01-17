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
