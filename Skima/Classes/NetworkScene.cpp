﻿#include "pch.h"
#include "NetworkScene.h"
#include "PacketType.h"
#include "RoomScene.h"
#include "TcpClient.h"
#include "SimpleAudioEngine.h"
#include "MakeRoomLayer.h"

using namespace CocosDenshion;

#define GET_CONNECT_LABEL dynamic_cast<Label*>(this->getChildByName("ConnectLabel"))
#define GET_MAKEROOM_LAYER dynamic_cast<Layer*>(this->getChildByName("MakeRoomLayer"))

Scene* NetworkScene::createScene()
{
    auto scene = Scene::create();
    auto layer = NetworkScene::create();
    scene->addChild(layer, 0, "NetworkScene");
    return scene;
}

bool NetworkScene::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    ConnectLabelCreate("방 참여 혹은 방 생성을 해주십시오.", this);

    auto background = Sprite::create("Images/Background/NetworkBackground.png");
    background->setPosition(winSize.width / 2, winSize.height / 2);
    background->setOpacity(150);
    this->addChild(background);

    auto createRoomButton = MenuItemImage::create("Images/Interface/CreateButton.png", "Images/Interface/CreateButton_selected.png",
        CC_CALLBACK_1(NetworkScene::menuCallback1, this));

    auto menu = Menu::create(createRoomButton, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    menu->setScale(1.3f);
    menu->setPosition(Vec2(winSize.width * 0.9f, winSize.height*0.2f));
    menu->alignItemsVertically();
    this->addChild(menu);

    this->schedule(schedule_selector(NetworkScene::Tick), 1.0f);

    return true;
}

void NetworkScene::menuCallback1(Ref* sender)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    if (GET_MAKEROOM_LAYER != nullptr)
        this->removeChildByName("MakeRoomLayer");

    auto makeRoomLayer = MakeRoomLayer::create();
    this->addChild(makeRoomLayer, 3, "MakeRoomLayer");
}

void NetworkScene::menuCallback2(int roomNum)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    ConnectLabelChange("방에 들어가는 중...");
    for (auto& room : m_RoomList)
    {
        if (room.mRoomNum == roomNum)
        {
            if (room.mCurPlayerNum >= room.mMaxPlayerNum) // 들어가려 한 방이 꽉차있을 때
            {
                ConnectLabelChange("방의 인원이 초과하였습니다.");
                return;
            }
            TcpClient::getInstance()->joinRoomRequest(room);
            break;
        }
    }
}

void NetworkScene::menuCallback3(Ref* sender)	// 나가기
{
    TcpClient::getInstance()->disconnect();
    Director::getInstance()->popScene();
}




void NetworkScene::ConnectLabelCreate(const char* str, NetworkScene* scene)
{
    if (scene->getChildByName("ConnectLabel") != nullptr)
    {
        scene->removeChildByName("ConnectLabel");
    }
    auto label = Label::createWithSystemFont(str, "Thonburi", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    scene->addChild(label, 0, "ConnectLabel");
}

void NetworkScene::ConnectLabelChange(const char* str)
{
    auto label = GET_CONNECT_LABEL;
    if (label != nullptr)
    {
        label->setString(str);
    }
}

void NetworkScene::RoomInformation(RoomInfo roomInfo)
{
    m_RoomList.push_back(roomInfo);
}

void NetworkScene::ClearRoomInfo()
{
    m_RoomList.clear();
}

void NetworkScene::UpdateRoomInfo()
{
    //Update를 위한 남아있는 Sprite 초기화
    while (this->getChildByName("RoomListFrame") != nullptr)
    {
        this->removeChildByName("RoomListFrame");
    }

    auto winSize = Director::getInstance()->getWinSize();
    auto line = 0.9f;

    for (auto& room : m_RoomList)
    {
        if (room.mRoomNum <= 0)
            break;

        auto roomListFrame = Sprite::create("Images/Interface/RoomListFrame.png");
        roomListFrame->setPosition(Vec2(winSize.width * 0.45f - 50, winSize.height * line));
        roomListFrame->setScaleX(1.50f);
        this->addChild(roomListFrame, 1, "RoomListFrame");

        auto roomListFrameBack = Sprite::create("Images/Interface/RoomListFrame_back.png");
        roomListFrameBack->setPosition(Vec2(405.0f, 115.0f));
        roomListFrameBack->setScaleX(1.10f);
        roomListFrameBack->setOpacity(150);
        roomListFrame->addChild(roomListFrameBack);
        auto joinRoomButton = MenuItemImage::create(
            "Images/Interface/JoinButton.png", 
            "Images/Interface/JoinButton_selected.png",
            CC_CALLBACK_0(NetworkScene::menuCallback2, this, room.mRoomNum));
        auto menu = Menu::create(joinRoomButton, NULL);
        menu->setPosition(Vec2(600.0f, 110.0f));
        menu->alignItemsVertically();
        joinRoomButton->setScaleX(0.8f);
        roomListFrame->addChild(menu);

        auto roomInfoLabel = Label::createWithSystemFont(" ", "Thonburi", 40);
        std::string roomInfo;   char buf[4];
        _itoa(room.mRoomNum, buf, 10);      std::string roomNum = buf;
        _itoa(room.mCurPlayerNum, buf, 10); std::string curPlayerNum = buf;
        _itoa(room.mMaxPlayerNum, buf, 10); std::string maxPlayerNum = buf;
        roomInfo += roomNum + "번 방       " + curPlayerNum + "명 / " + maxPlayerNum + "명";
        roomInfoLabel->setString(roomInfo);
        roomInfoLabel->setPosition(Vec2(240.0f, 110.0f));
        roomInfoLabel->setScaleX(0.8f);
        roomListFrame->addChild(roomInfoLabel);


        line -= 0.12f;
    }
}

void NetworkScene::MakeRoomComplete(RoomInfo roomInfo)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    ConnectLabelChange("서버 연결 양호.");
    auto scene = RoomScene::createScene();
    auto layer = dynamic_cast<RoomScene*>(scene->getChildByName("RoomScene"));
    layer->UpdateRoomInfo(roomInfo);
    Director::getInstance()->pushScene(scene);
}

void NetworkScene::JoinRoomComplete(RoomInfo roomInfo)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    ConnectLabelChange("서버 연결 양호.");
    auto scene = RoomScene::createScene();
    auto layer = dynamic_cast<RoomScene*>(scene->getChildByName("RoomScene"));
    layer->UpdateRoomInfo(roomInfo);
    Director::getInstance()->pushScene(scene);
}

void NetworkScene::Tick(float dt)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
    {
        Director::getInstance()->popScene();
    }
    ConnectLabelChange("서버 연결 양호.");
}