#include "pch.h"
#include "NetworkScene.h"
#include "SingleGameScene.h"
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
    if (!LayerColor::initWithColor(Color4B(100, 100, 200, 255)))
    {
        return false;
    }
    
    auto label0 = Label::createWithSystemFont("서버 접속", "Thonburi", 50);
    auto label1 = Label::createWithSystemFont("방 생성", "Thonburi", 50);
    auto label2 = Label::createWithSystemFont("방 참여", "Thonburi", 50);
    auto label3 = Label::createWithSystemFont("나가기", "Thonburi", 50);

    auto menuItem0 = MenuItemLabel::create(label0, CC_CALLBACK_1(NetworkScene::menuCallback0, this));
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(NetworkScene::menuCallback1, this));
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(NetworkScene::menuCallback2, this));
    auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(NetworkScene::menuCallback3, this));

    auto menu = Menu::create(menuItem0, menuItem1, menuItem2, menuItem3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu, 0, "NetworkMenu");

    // 3초 마다 Tick 함수를 호출한다.
    this->schedule(schedule_selector(NetworkScene::Tick), 3.0f);
    return true;
}

void NetworkScene::menuCallback0(Ref* sender)	// 서버 접속
{
    if (TcpClient::getInstance()->checkSocket() != NULL)
        return;

    ConnectLabelCreate("서버에 접속 중......", this);
    if (TcpClient::getInstance()->connect() == false)
    {
        TcpClient::getInstance()->disconnect();
        GET_CONNECT_LABEL->setString("서버 연결 실패.");
        return;
    }
    TcpClient::getInstance()->loginRequest();
}

void NetworkScene::menuCallback1(Ref* sender)	// 방 생성
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    ConnectLabelChange("방 생성 중...");
    TcpClient::getInstance()->makeRoomRequest();	
}

void NetworkScene::menuCallback2(Ref* sender)	// 방 참여
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
        return;

    ConnectLabelChange("방에 들어가는 중...");
    TcpClient::getInstance()->joinRoomRequest();
}

void NetworkScene::menuCallback3(Ref* sender)	// 나가기
{
    TcpClient::getInstance()->disconnect();
    Director::getInstance()->popScene();
}



//////////////////////////////////////////////////////////////////////////
void NetworkScene::Tick(float dt)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
    {
        ConnectLabelChange("서버 연결 끊김.");
    }
    else if (TcpClient::getInstance()->getLoginId() == -1)
    {
        TcpClient::getInstance()->loginRequest();
    }
    else
    {
        ConnectLabelChange("서버 연결 양호.");
    }
    ShowCursor(true);
}
//////////////////////////////////////////////////////////////////////////



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
