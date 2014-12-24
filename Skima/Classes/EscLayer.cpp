﻿#include "pch.h"
#include "EscLayer.h"
#include "GameScene.h"
#include "TcpClient.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool EscLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0,0,0,0))) //검은색 세팅
    {
        return false;
    }
    this->setOpacity(210);

    auto label1 = Label::createWithSystemFont("돌아가기", "Thonburi", 50);
    auto label2 = Label::createWithSystemFont("나가기", "Thonburi", 50);
    label1->setOpacity(255);
    label2->setOpacity(255);

    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(EscLayer::menuCallback1, this));
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(EscLayer::menuCallback2, this));

    auto menu = Menu::create(menuItem1, menuItem2, NULL);
    menu->alignItemsVertically();
    this->addChild(menu, 0, "EscMenu");
    //menu->setPosition(300, 300);

    return true;
}

void EscLayer::menuCallback1(Ref* sender)
{
    this->setVisible(false);
}

void EscLayer::menuCallback2(Ref* sender)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/mainscene.mp3", true);

    if (TcpClient::getInstance()->checkSocket() == NULL)
    {
        return;
    }

    auto m_Scene = dynamic_cast<GameScene*>(this->getParent());
    int roomId = m_Scene->GetRoomID();

    TcpClient::getInstance()->outRoomRequest(roomId);
    TcpClient::getInstance()->disconnect();
    ShowCursor(true);

    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
}

void EscLayer::ShowEscLayer()
{
    this->setVisible(true);

}
