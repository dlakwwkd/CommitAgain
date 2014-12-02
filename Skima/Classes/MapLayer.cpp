#include "pch.h"
#include "MapLayer.h"


bool MapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto layerCenter = this->getAnchorPointInPoints();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto sprite = Sprite::create("Images/bg1.png");
    sprite->setPosition(layerCenter);
    this->addChild(sprite);
    return true;
}
