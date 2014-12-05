#include "pch.h"
#include "RoomScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "MultiGameScene.h"
#include "CharacterSelectLayer.h"

#define GET_ROOM_STATE_LABEL dynamic_cast<Label*>(this->getChildByName("RoomStateLabel"))

Scene* RoomScene::createScene()
{
    auto scene = Scene::create();
    auto layer = RoomScene::create();
    scene->addChild(layer, 0, "RoomScene");
    return scene;
}

bool RoomScene::init()
{
    if (!LayerColor::initWithColor(Color4B(100, 100, 200, 255)))
    {
        return false;
    }

    m_RoomID = -1;
    m_IsReady = false;
    auto winSize = Director::getInstance()->getWinSize();

    auto label1 = Label::createWithSystemFont("게임 시작", "Thonburi", 50);
    auto label2 = Label::createWithSystemFont("나가기", "Thonburi", 50);

    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(RoomScene::menuCallback1, this));
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(RoomScene::menuCallback2, this));
    menuItem2->setPositionX(winSize.width * 1 / 8);

    auto menu = Menu::create(menuItem1, menuItem2, NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(winSize.width * 3 / 8, winSize.height * 7 / 8);
    this->addChild(menu, 0, "RoomMenu");

    auto layer = CharacterSelectLayer::create();
    this->addChild(layer, 10, "CharacterSelectLayer");
    

    auto label = Label::createWithSystemFont("연결 중...", "Thonburi", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(label, 0, "RoomStateLabel");

    // 1초 마다 Tick 함수를 호출한다.
    this->schedule(schedule_selector(RoomScene::Tick), 1.0f);
    return true;
}

void RoomScene::menuCallback1(Ref* sender)	// 게임 시작
{
    if (TcpClient::getInstance()->checkSocket() == NULL || m_IsReady)
        return;

    m_IsReady = true;
    TcpClient::getInstance()->startGameRequest(m_RoomID);
}

void RoomScene::menuCallback2(Ref* sender)	// 나가기
{
    if (TcpClient::getInstance()->checkSocket() != NULL)
        TcpClient::getInstance()->outRoomRequest(m_RoomID);

    m_IsReady = false;
    Director::getInstance()->popScene();
}



//////////////////////////////////////////////////////////////////////////
void RoomScene::Tick(float dt)
{
    auto label = GET_ROOM_STATE_LABEL;
    if(label == nullptr)
        return;

    // 방 번호를 문자열로 변환 후 라벨에 적용
    char buf[32];
    _itoa(m_RoomID, buf, 32);
    std::string roomNum = buf;
    roomNum += "번 방";
    label->setString(roomNum.c_str());
}
//////////////////////////////////////////////////////////////////////////



void RoomScene::GameStartComplete()
{
    auto scene = MultiGameScene::createScene();

    auto layer = dynamic_cast<MultiGameScene*>(scene->getChildByName("MultiGameScene"));
    layer->SetRoomID(m_RoomID);

    m_IsReady = false;
    Director::getInstance()->pushScene(scene);
}
