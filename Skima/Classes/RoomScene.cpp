#include "pch.h"
#include "RoomScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "GameScene.h"
#include "WaitingLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define GET_ROOM_STATE_LABEL dynamic_cast<Label*>(this->getChildByName("RoomStateLabel"))

Scene* RoomScene::createScene()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    auto scene = Scene::create();
    auto layer = RoomScene::create();
    scene->addChild(layer, 0, "RoomScene");
    return scene;
}

bool RoomScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    m_IsReady = false;
    auto winSize = Director::getInstance()->getWinSize();

    auto roomBackground = Sprite::create("Images/RoomBackground.png");
    roomBackground->setPosition(winSize.width / 2, winSize.height / 2);
    this->addChild(roomBackground, -1);
    auto selectZone = Sprite::create("Images/SelectZone.png");
    selectZone->setPosition(Vec2(winSize.width * 1 / 8, winSize.height * 3 / 8 - 30));
    selectZone->setOpacity(100);
    this->addChild(selectZone, 1);
        
    /////////////////////////////////////////////////캐릭터 초상화 추가할 부분/////////////////////////////////////////////
    /* Ready 캐릭터 전체모습 띄우는 부분 */
    MakeHeroSprite("Images/SelectFace/[Select]Magician.png", Vec2(winSize.width * 1 / 8 - 70, winSize.height * 4 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1), HERO_MAGICIAN);
    MakeHeroSprite("Jupiter/JupiterImage.png", Vec2(winSize.width * 1 / 8 - 50, winSize.height * 4 / 8), Vec2(1.5f, 1.5f), Vec2(0, 1), HERO_JUPITER);
    MakeHeroSprite("Laphinx/LaphinxImage.png", Vec2(winSize.width * 1 / 8 - 80, winSize.height * 4 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1), HERO_LAPHINX);

    /* 캐릭터 선택창버튼 초상화 추가 (width 1/8씩 ++) */
    auto magicanFace = MenuItemImage::create(
        "Images/SelectFace/[Select]Magician.png",
        "Images/SelectFace/[Select]Magician_selected.png",
        CC_CALLBACK_0(RoomScene::ClickHero, this, HERO_MAGICIAN));
    SetFaceProperty(magicanFace, Vec2(winSize.width * 1 / 8, winSize.height * 5 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1));
    auto jupiterFace = MenuItemImage::create(
        "Images/SelectFace/[Select]Jupiter.png",
        "Images/SelectFace/[Select]Jupiter_selected.png",
        CC_CALLBACK_0(RoomScene::ClickHero, this, HERO_JUPITER));
    SetFaceProperty(jupiterFace, Vec2(winSize.width * 2 / 8, winSize.height * 5 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1));
    auto laphinxFace = MenuItemImage::create(
        "Images/SelectFace/[Select]Laphinx.png", 
        "Images/SelectFace/[Select]Laphinx_selected.png",
        CC_CALLBACK_0(RoomScene::ClickHero, this, HERO_LAPHINX));
    SetFaceProperty(laphinxFace, Vec2(winSize.width * 3 / 8, winSize.height * 5 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1));

    auto faceTable = Menu::create(magicanFace, jupiterFace,laphinxFace, NULL);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    faceTable->setPosition(winSize.width * 3 / 8, winSize.height * 2 / 8);
    this->addChild(faceTable);

    m_CurHero = HERO_MAGICIAN;
    m_HeroImageList[HERO_MAGICIAN]->setVisible(true);

    auto readyButton = MenuItemImage::create("Images/GameReady.png", "Images/GameReady_Selected.png", CC_CALLBACK_1(RoomScene::GameStartCallback, this));
    auto exitButton = MenuItemImage::create("Images/ExitGame.png", "Images/ExitGame_Selected.png", CC_CALLBACK_1(RoomScene::GameExitCallback, this));
    exitButton->setPosition(Vec2(0, -80));
    exitButton->setScale(1.3f);
    auto buttonMenu = Menu::create(readyButton, exitButton, NULL); 
    buttonMenu->setPosition(winSize.width * 7 / 8 , winSize.height * 3 / 8);
    this->addChild(buttonMenu);

    m_WaitingLayer = WaitingLayer::create();
    m_WaitingLayer->setVisible(false);
    this->addChild(m_WaitingLayer, 2);

    auto label = Label::createWithSystemFont("연결 중...", "Thonburi", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setPosition(Vec2(0, winSize.height * 0.9f));
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
    TcpClient::getInstance()->startGameRequest(m_RoomID,m_CurHero);
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
    if (TcpClient::getInstance()->checkSocket() == NULL)
    {
        Director::getInstance()->popScene();
    }
    auto label = GET_ROOM_STATE_LABEL;
    if(label == nullptr)
        return;

    // 방 번호를 문자열로 변환 후 라벨에 적용
    char buf[4];
    _itoa(m_RoomID, buf, 10);
    std::string roomNum = buf;
    roomNum += "번 방";
    label->setString(roomNum);
 
}
//////////////////////////////////////////////////////////////////////////

void RoomScene::GameStartComplete()
{
    auto scene = GameScene::createScene();

    auto layer = dynamic_cast<GameScene*>(scene->getChildByName("GameScene"));
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

void RoomScene::MakeHeroSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor, HeroType hero)
{
    Sprite* sprite = Sprite::create(image);
    sprite->setPosition(pos);
    sprite->setScale(scale.x, scale.y);
    sprite->setAnchorPoint(anchor);
    sprite->setVisible(false);
    m_HeroImageList[hero] = sprite;
    this->addChild(sprite);
}

void RoomScene::SetFaceProperty(MenuItemImage* img, Vec2 pos, Vec2 scale, Vec2 anchor)
{
    img->setPosition(pos);
    img->setScale(scale.x, scale.y);
    img->setAnchorPoint(anchor);
}

void RoomScene::ChangeSelectedHero(HeroType heroType)
{
    for (auto& hero : m_HeroImageList)
    {
        hero.second->setVisible(false);
    }
    m_HeroImageList[heroType]->setVisible(true);

    auto winSize = Director::getInstance()->getWinSize();
    auto zoneEffect = Sprite::create("Images/ZoneEffect.png");
    zoneEffect->setPosition(Vec2(winSize.width * 1 / 8, winSize.height / 4));
    zoneEffect->setOpacity(100);
    this->addChild(zoneEffect, 2);

    auto zoneAction_0 = MoveTo::create(1.0f, Vec2(winSize.width * 1 / 8, winSize.height / 2));
    auto zoneAction_1 = FadeTo::create(1.5f, 0);
    zoneEffect->runAction(zoneAction_0);
    zoneEffect->runAction(zoneAction_1);
}

void RoomScene::ClickHero(HeroType heroType)
{
    m_CurHero = heroType;
    ChangeSelectedHero(heroType);
}

