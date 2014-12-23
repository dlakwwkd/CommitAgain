#include "pch.h"
#include "NetworkScene.h"
#include "PacketType.h"
#include "RoomScene.h"
#include "TcpClient.h"

#define GET_CONNECT_LABEL dynamic_cast<Label*>(this->getChildByName("ConnectLabel"))

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

    auto background = Sprite::create("Images/NetworkBackground.png");
    background->setPosition(winSize.width / 2, winSize.height / 2);
    background->setOpacity(150);
    this->addChild(background);

    auto createRoomButton = MenuItemImage::create("Images/CreateButton.png", "Images/CreateButton_selected.png",
        CC_CALLBACK_1(NetworkScene::menuCallback1, this));

    auto menu = Menu::create(createRoomButton, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    menu->setScale(1.3f);
    menu->setPosition(Vec2(winSize.width * 0.9f, winSize.height*0.2f));
    menu->alignItemsVertically();
    this->addChild(menu);

    this->schedule(schedule_selector(NetworkScene::Tick), 3.0f);

    return true;
}

void NetworkScene::menuCallback1(Ref* sender)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    ConnectLabelChange("방 생성 중...");
    TcpClient::getInstance()->makeRoomRequest();	
}

void NetworkScene::menuCallback2(int roomNum)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    ConnectLabelChange("방에 들어가는 중...");
    TcpClient::getInstance()->joinRoomRequest(roomNum);
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
    ConnectLabelChange("로그인 성공!!");
}

void NetworkScene::ClearRoomInfo()
{
    m_RoomList.clear();
}

void NetworkScene::UpdateRoomInfo()
{
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

        auto roomListFrame = Sprite::create("Images/RoomListFrame.png");
        roomListFrame->setPosition(Vec2(winSize.width * 0.45f - 50, winSize.height * line));
        roomListFrame->setScaleX(1.50f);
        this->addChild(roomListFrame, 1, "RoomListFrame");

        auto roomListFrameBack = Sprite::create("Images/RoomListFrame_back.png");
        roomListFrameBack->setPosition(Vec2(405.0f, 115.0f));
        roomListFrameBack->setScaleX(1.10f);
        roomListFrameBack->setOpacity(150);
        roomListFrame->addChild(roomListFrameBack);
        auto joinRoomButton = MenuItemImage::create(
            "Images/JoinButton.png", 
            "Images/JoinButton_selected.png",
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

void NetworkScene::MakeRoomComplete(int roomId)
{
    ConnectLabelChange("서버 연결 양호.");
    auto scene = RoomScene::createScene();
    auto layer = dynamic_cast<RoomScene*>(scene->getChildByName("RoomScene"));
    layer->SetRoomID(roomId);
    Director::getInstance()->pushScene(scene);
}

void NetworkScene::JoinRoomComplete(int roomId)
{
    ConnectLabelChange("서버 연결 양호.");
    auto scene = RoomScene::createScene();
    auto layer = dynamic_cast<RoomScene*>(scene->getChildByName("RoomScene"));
    layer->SetRoomID(roomId);
    Director::getInstance()->pushScene(scene);
}

void NetworkScene::Tick(float dt)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
    {
        Director::getInstance()->popScene();
    }
}