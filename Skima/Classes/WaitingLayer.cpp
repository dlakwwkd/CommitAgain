#include "pch.h"
#include "WaitingLayer.h"
#include "RoomScene.h"

#define GET_CONNECT_LABEL dynamic_cast<Label*>(this->getChildByName(CONNECT_LABEL))
#define GET_ROOM_SCENE    dynamic_cast<RoomScene*>(this->getParent())

bool WaitingLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK)) //검은색 세팅
        return false;
    this->setOpacity(240);

    auto winSize = Director::getInstance()->getWinSize();

    auto label = Label::create("다른 플레이어를 기다리는 중...", "Arial", 50);
    label->setPosition(Vec2(winSize.width / 2, winSize.height * 3 / 4));
    this->addChild(label, 1, CONNECT_LABEL);
    return true;
}

void WaitingLayer::GameStart()
{
    auto winSize = Director::getInstance()->getWinSize();

    auto label1 = GET_CONNECT_LABEL;
    if (label1 != nullptr)
    {
        label1->setString("게임을 시작합니다.");
        label1->setPositionY(winSize.height * 3 / 4);
    }
    auto label2 = Label::create("", "Arial", 100);
    label2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(label2);
    
    auto action0 = CallFunc::create(CC_CALLBACK_0(Label::setString, label2, "3"));
    auto action1 = DelayTime::create(1.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(Label::setString, label2, "2"));
    auto action3 = CallFunc::create(CC_CALLBACK_0(Label::setString, label2, "1"));
    auto action4 = CallFunc::create(CC_CALLBACK_0(RoomScene::GameStartComplete, GET_ROOM_SCENE));
    auto action5 = CallFunc::create(CC_CALLBACK_0(Label::setString, label1, "다른 플레이어를 기다리는 중..."));
    auto action6 = CallFunc::create(CC_CALLBACK_0(Label::setString, label2, " "));
    auto action = Sequence::create(action0, action1, action2,
        action1, action3, action1, action4, action5, action6, NULL);

    label2->runAction(action);
}
