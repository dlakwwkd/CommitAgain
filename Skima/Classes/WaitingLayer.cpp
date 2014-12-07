#include "pch.h"
#include "WaitingLayer.h"

bool WaitingLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0,0,0,0))) //검은색 세팅
    {
        return false;
    }
    this->setOpacity(240);

    auto winSize = Director::getInstance()->getWinSize();

    auto label = LabelTTF::create("Please Wait", "Arial", 50);
    label->setPosition(winSize.width/2, winSize.height/2);
    this->addChild(label);

    return true;
}

