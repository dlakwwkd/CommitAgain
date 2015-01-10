#include "pch.h"
#include "RoomScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "GameScene.h"
#include "WaitingLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define GET_TEAM_STATE_LABEL dynamic_cast<Label*>(this->getChildByName(TEAM_STATE_LABEL))
#define GET_ROOM_STATE_LABEL dynamic_cast<Label*>(this->getChildByName(ROOM_STATE_LABEL))
#define GET_ROOM_PLAYER_LABEL dynamic_cast<Label*>(this->getChildByName(PLAYER_NUM_LABEL))
#define GET_WAITING_LAYER    dynamic_cast<WaitingLayer*>(this->getChildByName(WAITING_LAYER))

Scene* RoomScene::createScene()
{
    auto scene = Scene::create();
    auto layer = RoomScene::create();
    scene->addChild(layer, 0, ROOM_SCENE);
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

    auto roomBackground = Sprite::create("Images/Background/RoomBackground.png");
    roomBackground->setPosition(winSize.width / 2, winSize.height / 2);
    roomBackground->setOpacity(150);
    this->addChild(roomBackground, -1);
    auto selectZone = Sprite::create("Images/Interface/SelectZone.png");
    selectZone->setPosition(Vec2(winSize.width / 4, winSize.height * 3 / 8 - 30));
    selectZone->setOpacity(100);
    this->addChild(selectZone, 1);
        
    /////////////////////////////////////////////////캐릭터 초상화 추가할 부분/////////////////////////////////////////////
    /* Ready 캐릭터 전체모습 띄우는 부분 */
    MakeHeroSprite("Images/Unit/Magician/MagicianImage.png", Vec2(winSize.width * 2 / 8 - 50, winSize.height * 4 / 8 - 50), Vec2(1.5f, 1.5f), Vec2(0, 1), HERO_MAGICIAN);
    MakeHeroSprite("Images/Unit/Jupiter/JupiterImage.png", Vec2(winSize.width * 2 / 8 - 50, winSize.height * 4 / 8 - 10), Vec2(1.5f, 1.5f), Vec2(0, 1), HERO_JUPITER);
    MakeHeroSprite("Images/Unit/Laphinx/LaphinxImage.png", Vec2(winSize.width * 2 / 8 - 80, winSize.height * 4 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1), HERO_LAPHINX);

    /* 캐릭터 선택창버튼 초상화 추가 (width 1/8씩 ++) */
    auto magicanFace = MenuItemImage::create(
        "Images/Interface/[Select]Magician.png",
        "Images/Interface/[Select]Magician_selected.png",
        CC_CALLBACK_0(RoomScene::ClickHero, this, HERO_MAGICIAN));
    SetFaceProperty(magicanFace, Vec2(winSize.width * 1 / 8, winSize.height * 5 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1));
    auto jupiterFace = MenuItemImage::create(
        "Images/Interface/[Select]Jupiter.png",
        "Images/Interface/[Select]Jupiter_selected.png",
        CC_CALLBACK_0(RoomScene::ClickHero, this, HERO_JUPITER));
    SetFaceProperty(jupiterFace, Vec2(winSize.width * 2 / 8, winSize.height * 5 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1));
    auto laphinxFace = MenuItemImage::create(
        "Images/Interface/[Select]Laphinx.png", 
        "Images/Interface/[Select]Laphinx_selected.png",
        CC_CALLBACK_0(RoomScene::ClickHero, this, HERO_LAPHINX));
    SetFaceProperty(laphinxFace, Vec2(winSize.width * 3 / 8, winSize.height * 5 / 8), Vec2(1.0f, 1.0f), Vec2(0, 1));

    auto faceTable = Menu::create(magicanFace, jupiterFace,laphinxFace, NULL);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    faceTable->setPosition(winSize.width * 4 / 8, winSize.height * 2 / 8);
    this->addChild(faceTable);

    m_CurHero = HERO_MAGICIAN;
    m_CurTeam = TEAM_1;
    m_HeroImageList[HERO_MAGICIAN]->setVisible(true);

    auto waitLayer = WaitingLayer::create();
    waitLayer->setVisible(false);
    this->addChild(waitLayer, 2, WAITING_LAYER);

    auto label1 = Label::createWithSystemFont(ROOM_INFO_WAITING_TEXT, DEF_FONT, 70);
    label1->setAnchorPoint(Vec2(0, 0));
    label1->setPosition(Vec2(0, winSize.height * 0.9f));
    label1->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(label1, 0, ROOM_STATE_LABEL);

    auto label2 = Label::createWithSystemFont(" ", DEF_FONT, 50);
    label2->setAnchorPoint(Vec2(0, 0));
    label2->setPosition(Vec2(0, winSize.height * 0.7f));
    label2->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(label2, 0, PLAYER_NUM_LABEL);

    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/banpick.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);

    // 1초 마다 Tick 함수를 호출한다.
    this->schedule(schedule_selector(RoomScene::Tick), 1.0f);
    return true;
}

/// 팀 선택 정보 표시 임시방편...
//////////////////////////////////////////////////////////////////////////
void RoomScene::TeamSelectACallback(Ref* sender)
{
    auto label = GET_TEAM_STATE_LABEL;
    if (label == nullptr)
        return;
    m_CurTeam = TEAM_1;
    label->setString(TEAM_1_TEXT);
}

void RoomScene::TeamSelectBCallback(Ref* sender)
{
    auto label = GET_TEAM_STATE_LABEL;
    if (label == nullptr)
        return;
    m_CurTeam = TEAM_2;
    label->setString(TEAM_2_TEXT);
}
//////////////////////////////////////////////////////////////////////////

void RoomScene::GameStartCallback(Ref* sender)	// 게임 시작
{
    if (TcpClient::getInstance()->checkSocket() == NULL || m_IsReady)
    {
        return;
    }
    m_IsReady = true;
    WaitingCheck();
    TcpClient::getInstance()->startGameRequest(m_RoomInfo.mRoomNum, m_CurTeam, m_CurHero);
}

void RoomScene::GameExitCallback(Ref* sender)	// 나가기
{
    if (TcpClient::getInstance()->checkSocket() != NULL)
    {
        TcpClient::getInstance()->outRoomRequest(m_RoomInfo);
    }

    m_IsReady = false;
    WaitingCheck();

    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/mainscene.mp3", true);

    Director::getInstance()->popScene();
}

//////////////////////////////////////////////////////////////////////////
void RoomScene::Tick(float dt)
{
    if (TcpClient::getInstance()->checkSocket() == NULL)
    {
        Director::getInstance()->popScene();
    }
    auto label1 = GET_ROOM_STATE_LABEL;
    if(label1 == nullptr)
        return;

    // 방 번호를 문자열로 변환 후 라벨에 적용
    char buf[4];
    _itoa(m_RoomInfo.mRoomNum, buf, 10);
    std::string roomNum = buf;
    roomNum += ROOM_NUM_TEXT;
    label1->setString(roomNum);
}
//////////////////////////////////////////////////////////////////////////
void RoomScene::UpdateRoomInfo(RoomInfo roomInfo)
{
    auto label2 = GET_ROOM_PLAYER_LABEL;
    if (label2 == nullptr)
        return;

    m_RoomInfo = roomInfo;

    char buf[4];
    std::string roomInfoStr = PLAYER_NUM_TEXT;
    _itoa(m_RoomInfo.mCurPlayerNum, buf, 10);
    std::string curPlayerNum = buf;
    curPlayerNum += "명 / ";
    _itoa(m_RoomInfo.mMaxPlayerNum, buf, 10);
    std::string maxPlayerNum = buf;
    maxPlayerNum += "명";
    roomInfoStr += curPlayerNum + maxPlayerNum;
    label2->setString(roomInfoStr);
}

void RoomScene::GameStart()
{
    GET_WAITING_LAYER->GameStart();
}

void RoomScene::GameStartComplete()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    auto scene = GameScene::createScene();

    auto layer = dynamic_cast<GameScene*>(scene->getChildByName(GAME_SCENE));
    layer->SetRoomInfo(m_RoomInfo);

    m_IsReady = false;
    WaitingCheck();
    Director::getInstance()->pushScene(scene);
    TcpClient::getInstance()->loadingOKRequest();
}

void RoomScene::WaitingCheck()
{
    if (m_IsReady == true)
    {
        GET_WAITING_LAYER->setVisible(true);
    }
    else
    {
        GET_WAITING_LAYER->setVisible(false);
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
    auto zoneEffect = Sprite::create("Images/Interface/ZoneEffect.png");
    zoneEffect->setPosition(Vec2(winSize.width / 4, winSize.height / 4));
    zoneEffect->setOpacity(100);
    this->addChild(zoneEffect, 2);

    auto zoneAction_0 = MoveTo::create(1.0f, Vec2(winSize.width / 4, winSize.height / 2));
    auto zoneAction_1 = FadeTo::create(1.5f, 0);
    zoneEffect->runAction(zoneAction_0);
    zoneEffect->runAction(zoneAction_1);
}
void RoomScene::ClickHero(HeroType heroType)
{
    m_CurHero = heroType;
    ChangeSelectedHero(heroType);
}

void RoomScene::PrintMenuByRoomType()
{
    auto winSize = Director::getInstance()->getWinSize();

    switch (m_RoomInfo.mRoomType)
    {
    case ROOM_NONE:
        break;
    case ROOM_MELEE:
    {
         auto roomTypeImage = Sprite::create("Images/Interface/MeleeModeButton.png");
         roomTypeImage->setPosition(Vec2(winSize.width / 2, winSize.height * 7 / 8));
         this->addChild(roomTypeImage);
         auto readyButton = MenuItemImage::create("Images/Interface/GameReady.png", "Images/Interface/GameReady_Selected.png", CC_CALLBACK_1(RoomScene::GameStartCallback, this));
         auto exitButton = MenuItemImage::create("Images/Interface/ExitGame.png", "Images/Interface/ExitGame_Selected.png", CC_CALLBACK_1(RoomScene::GameExitCallback, this));
         exitButton->setPosition(Vec2(0, -80));
         exitButton->setScale(1.3f);
         auto buttonMenu = Menu::create(readyButton, exitButton, NULL);
         buttonMenu->setPosition(winSize.width * 7 / 8, winSize.height * 3 / 8);
         this->addChild(buttonMenu);
         break;
    }
    case ROOM_TEAM:
    {
         auto roomTypeImage = Sprite::create("Images/Interface/TeamModeButton.png");
         roomTypeImage->setPosition(Vec2(winSize.width / 2, winSize.height * 7 / 8));
         this->addChild(roomTypeImage);
         auto label1 = Label::createWithSystemFont(TEAM_1_TEXT, DEF_FONT, 50);
         auto teamButton1 = MenuItemLabel::create(label1, CC_CALLBACK_1(RoomScene::TeamSelectACallback, this));
         teamButton1->setPosition(Vec2(-80, 80));
         auto label2 = Label::createWithSystemFont(TEAM_2_TEXT, DEF_FONT, 50);
         auto teamButton2 = MenuItemLabel::create(label2, CC_CALLBACK_1(RoomScene::TeamSelectBCallback, this));
         teamButton2->setPosition(Vec2(80, 80));
         
         auto label3 = Label::createWithSystemFont(TEAM_1_TEXT, DEF_FONT, 50);
         label3->setPosition(Vec2(100, winSize.height * 0.5f));
         label3->setHorizontalAlignment(TextHAlignment::CENTER);
         this->addChild(label3, 0, TEAM_STATE_LABEL);
         
         auto readyButton = MenuItemImage::create("Images/Interface/GameReady.png", "Images/Interface/GameReady_Selected.png", CC_CALLBACK_1(RoomScene::GameStartCallback, this));
         auto exitButton = MenuItemImage::create("Images/Interface/ExitGame.png", "Images/Interface/ExitGame_Selected.png", CC_CALLBACK_1(RoomScene::GameExitCallback, this));
         exitButton->setPosition(Vec2(0, -80));
         exitButton->setScale(1.3f);
         auto buttonMenu = Menu::create(readyButton, exitButton, teamButton1, teamButton2, NULL);
         buttonMenu->setPosition(winSize.width * 7 / 8, winSize.height * 3 / 8);
         this->addChild(buttonMenu);
         break;
    }
    default:
        break;
    }
}

