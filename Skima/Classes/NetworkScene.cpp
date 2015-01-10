#include "pch.h"
#include "NetworkScene.h"
#include "PacketType.h"
#include "RoomScene.h"
#include "TcpClient.h"
#include "SimpleAudioEngine.h"
#include "MakeRoomLayer.h"

using namespace CocosDenshion;

#define GET_CONNECT_LABEL dynamic_cast<Label*>(this->getChildByName(CONNECT_LABEL))
#define GET_MAKEROOM_LAYER dynamic_cast<Layer*>(this->getChildByName(MAKEROOM_LAYER))

Scene* NetworkScene::createScene()
{
    auto scene = Scene::create();
    auto layer = NetworkScene::create();
    scene->addChild(layer, 0, NETWORK_SCENE);
    return scene;
}

bool NetworkScene::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    ConnectLabelCreate(CONNECT_SUCCESS_TEXT, this);

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
        this->removeChildByName(MAKEROOM_LAYER);

    auto makeRoomLayer = MakeRoomLayer::create();
    this->addChild(makeRoomLayer, 3, MAKEROOM_LAYER);
}

void NetworkScene::menuCallback2(int roomNum)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    ConnectLabelChange(TRY_JOIN_ROOM_TEXT);
    for (auto& room : m_RoomList)
    {
        if (room.mRoomNum == roomNum)
        {
            if (room.mIsAllReady) //들어가려한 방이 게임이 시작된 방일 때
            {
                ConnectLabelChange(ROOM_IS_STARTED_TEXT);
                return;
            }
            if (room.mCurPlayerNum >= room.mMaxPlayerNum) // 들어가려한 방이 꽉차있을 때
            {
                ConnectLabelChange(ROOM_IS_FULL_TEXT);
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
    if (scene->getChildByName(CONNECT_LABEL) != nullptr)
    {
        scene->removeChildByName(CONNECT_LABEL);
    }
    auto label = Label::createWithSystemFont(str, DEF_FONT, 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    scene->addChild(label, 0, CONNECT_LABEL);
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
    while (this->getChildByName(ROOM_LIST_FRAME) != nullptr)
    {
        this->removeChildByName(ROOM_LIST_FRAME);
    }

    auto winSize = Director::getInstance()->getWinSize();
    auto line = 0.9f;

    for (auto& room : m_RoomList)
    {
        if (room.mRoomNum <= 0)
            break;

        auto roomListFrame = Sprite::create("Images/Interface/RoomListFrame.png");
        roomListFrame->setPosition(Vec2(winSize.width * 0.45f - 50, winSize.height * line));
        roomListFrame->setScaleX(1.5f);
        this->addChild(roomListFrame, 1, ROOM_LIST_FRAME);

        auto roomListFrameBack = Sprite::create("Images/Interface/RoomListFrame_back.png");
        roomListFrameBack->setPosition(Vec2(505.0f, 115.0f));
        roomListFrameBack->setScaleX(1.10f);
        roomListFrameBack->setOpacity(150);
        roomListFrame->addChild(roomListFrameBack);
        switch (room.mRoomType)
        {
        case ROOM_NONE:
        {
            break;
        }
        case ROOM_MELEE:
        {
            auto roomType = Sprite::create("Images/Interface/MeleeModeButton.png");
            roomType->setScaleX(0.7f);
            roomType->setPosition(Vec2(550.0f, 110.0f));
            roomListFrame->addChild(roomType);
            break;
        }
        case ROOM_TEAM:
        {
            auto roomType = Sprite::create("Images/Interface/TeamModeButton.png");
            roomType->setScaleX(0.7f);
            roomType->setPosition(Vec2(550.0f, 110.0f));
            roomListFrame->addChild(roomType);
            break;
        }
        default:
        {
            break;
        }
        }
        auto joinRoomButton = MenuItemImage::create(
            "Images/Interface/JoinButton.png", 
            "Images/Interface/JoinButton_selected.png",
            CC_CALLBACK_0(NetworkScene::menuCallback2, this, room.mRoomNum));
        auto menu = Menu::create(joinRoomButton, NULL);
        menu->setPosition(Vec2(800.0f, 110.0f));
        menu->alignItemsVertically();
        joinRoomButton->setScaleX(0.8f);
        roomListFrame->addChild(menu);

        auto roomInfoLabel = Label::createWithSystemFont(" ", DEF_FONT, 40);
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
    ConnectLabelChange(CONNECT_GOOD_TEXT);
    auto scene = RoomScene::createScene();
    auto layer = dynamic_cast<RoomScene*>(scene->getChildByName(ROOM_SCENE));
    layer->UpdateRoomInfo(roomInfo);
    layer->PrintMenuByRoomType();
    Director::getInstance()->pushScene(scene);
}

void NetworkScene::JoinRoomComplete(RoomInfo roomInfo)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    ConnectLabelChange(CONNECT_GOOD_TEXT);
    auto scene = RoomScene::createScene();
    auto layer = dynamic_cast<RoomScene*>(scene->getChildByName(ROOM_SCENE));
    layer->UpdateRoomInfo(roomInfo);
    layer->PrintMenuByRoomType();
    Director::getInstance()->pushScene(scene);
}

void NetworkScene::Tick(float dt)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
    {
        Director::getInstance()->popScene();
    }
    ConnectLabelChange(JOIN_ROOM_REQUEST_TEXT);
}