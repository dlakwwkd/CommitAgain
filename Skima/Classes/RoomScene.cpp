#include "pch.h"
#include "RoomScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "MultiGameScene.h"
#include "WaitingLayer.h"

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
    if (!LayerColor::initWithColor(Color4B(0, 0, 128, 128)))
    {
        return false;
    }

    m_RoomID = -1;
    m_IsReady = false;
    auto winSize = Director::getInstance()->getWinSize();
        
    /////////////////////////////////////////////////캐릭터 초상화 추가할 부분/////////////////////////////////////////////
    /* Ready 캐릭터 띄울 얼굴추가 */
    MakeFaceSprite("Images/SelectFace/[Select]Magician.png", Vec2(winSize.width * 1 / 8, winSize.height * 3 / 4), Vec2(1.0f, 1.0f), Vec2(0, 1), HERO_MAGICIAN);
    MakeFaceSprite("Images/SelectFace/[Select]Jupiter.png", Vec2(winSize.width * 1 / 8, winSize.height * 3 / 4), Vec2(1.0f, 1.0f), Vec2(0, 1), HERO_JUPITER);

    /* 캐릭터 선택창버튼 초상화 추가 (width 1/8씩 ++) */
    auto magicanFace = MenuItemImage::create("Images/SelectFace/[Select]Magician.png", "Images/SelectFace/[Select]Magician_selected.png", CC_CALLBACK_0(RoomScene::ClickMagician, this));
    SetFaceProperty(magicanFace, Vec2(winSize.width * 1 / 8, winSize.height * 1 / 4), Vec2(1.0f, 1.0f), Vec2(0, 1));
    auto jupiterFace = MenuItemImage::create("Images/SelectFace/[Select]Jupiter.png", "Images/SelectFace/[Select]Jupiter_selected.png", CC_CALLBACK_0(RoomScene::ClickJupiter, this));
    SetFaceProperty(jupiterFace, Vec2(winSize.width * 2 / 8, winSize.height * 1 / 4), Vec2(1.0f, 1.0f), Vec2(0, 1));
    
    auto faceTable = Menu::create(magicanFace, jupiterFace, NULL);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    faceTable->setPosition(winSize.width * 1 / 8, winSize.height * 2 / 8);
    this->addChild(faceTable);

    m_CurHero = HERO_MAGICIAN;
    m_Facelist[HERO_MAGICIAN]->setVisible(true);

    auto readyButton = MenuItemImage::create("Images/GameReady.png", "Images/GameReady_selected.png", CC_CALLBACK_1(RoomScene::GameStartCallback, this));
    auto exitButton = MenuItemImage::create("Images/Gameout.png", "Images/Gameout_selected.png", CC_CALLBACK_1(RoomScene::GameExitCallback, this));
    exitButton->setPosition(winSize.width*1/8,winSize.height*-4/8);
    readyButton->setScale(0.8f, 0.8f);
    exitButton->setScale(0.7f, 0.7f);
    auto buttonMenu = Menu::create(readyButton, exitButton, NULL); 
    buttonMenu->setPosition(winSize.width * 3 / 8, winSize.height * 11 / 16);
    this->addChild(buttonMenu);

    m_WaitingLayer = WaitingLayer::create();
    m_WaitingLayer->setVisible(false);
    this->addChild(m_WaitingLayer);

    auto label = Label::createWithSystemFont("연결 중...", "Thonburi", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(label, 0, "RoomStateLabel");

    // 1초 마다 Tick 함수를 호출한다.
    this->schedule(schedule_selector(RoomScene::Tick), 1.0f);
    return true;
}

void RoomScene::GameStartCallback(Ref* sender)	// 게임 시작
{
    if (TcpClient::getInstance()->checkSocket() == NULL || m_IsReady)
    {
        return;
    }
    m_IsReady = true;
    WaitingCheck();
    TcpClient::getInstance()->startGameRequest(m_RoomID);
}

void RoomScene::GameExitCallback(Ref* sender)	// 나가기
{
    if (TcpClient::getInstance()->checkSocket() != NULL)
    {
        TcpClient::getInstance()->outRoomRequest(m_RoomID);
    }

    m_IsReady = false;
    WaitingCheck();
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
    WaitingCheck();
    Director::getInstance()->pushScene(scene);
}

void RoomScene::WaitingCheck()
{
    if (m_IsReady == true)
    {
        m_WaitingLayer->setVisible(true);
    }
    else
    {
        m_WaitingLayer->setVisible(false);
    }
}

void RoomScene::MakeFaceSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor, HeroType hero)
{
    Sprite* sprite = Sprite::create(image);
    sprite->setPosition(pos);
    sprite->setScale(scale.x, scale.y);
    sprite->setAnchorPoint(anchor);
    sprite->setVisible(false);
    m_Facelist[hero] = sprite;
    this->addChild(sprite);
}

void RoomScene::SetFaceProperty(MenuItemImage* img, Vec2 pos, Vec2 scale, Vec2 anchor)
{
    img->setPosition(pos);
    img->setScale(scale.x, scale.y);
    img->setAnchorPoint(anchor);
}

void RoomScene::ChangeSelectedHero()
{
    switch (m_CurHero)
    {
    case HERO_MAGICIAN:
        for (auto& select : m_Facelist)
        {
            select.second->setVisible(false);
            if (select.first == HERO_MAGICIAN)
            {
                select.second->setVisible(true);
            }
        }
        break;
    case HERO_JUPITER:
        for (auto& select : m_Facelist)
        {
            select.second->setVisible(false);
            if (select.first == HERO_JUPITER)
            {
                select.second->setVisible(true);
            }
        }
        break;
    case HERO_NONE:
        break;
    }
}

void RoomScene::ClickMagician()
{
    m_CurHero = HERO_MAGICIAN;
    ChangeSelectedHero();
}
void RoomScene::ClickJupiter()
{
    m_CurHero = HERO_JUPITER;
    ChangeSelectedHero();
}

