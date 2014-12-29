#include "pch.h"
#include "MainScene.h"
#include "NetworkScene.h"
#include "RoomScene.h"
#include "InputBox.h"
#include "TcpClient.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define MAX_NAME_LEN 14
#define GET_CONNECT_LABEL dynamic_cast<Label*>(this->getChildByName("ConnectLabel"))

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer, 0, "MainScene");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Background/mainscene.mp3");
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();

    // 배경화면 plist 보여주는 부분
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_01.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_02.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_03.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_04.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_05.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_06.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_07.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_08.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_09.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Background/MainBackground_10.plist");

    auto background1 = Sprite::createWithSpriteFrameName("MainBackground_001.png");
    auto background2 = Sprite::create("Images/Background/MainBackground2.png");
    auto title = Sprite::create("Images/Background/SkimaTitle.png");
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.2f);

    for (int i = 1; i <= 196; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("MainBackground_%003d.png", i));
        animation->addSpriteFrame(frame);
    }
    background1->runAction(RepeatForever::create(Animate::create(animation)));
    background1->setScaleX(2.70f);
    background1->setScaleY(2.30f);
    background1->setAnchorPoint(Vec2::ZERO);
    background2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    background2->setOpacity(50);
    title->setPosition(Vec2(winSize.width / 2, winSize.height * 3 / 4));
    title->setScale(1.30f);
    this->addChild(background1);
    this->addChild(background2);
    this->addChild(title);

    // Login창 띄우기
    auto loginScene = Sprite::create("Images/Interface/LoginScene.png");
    loginScene->setPosition(Vec2(winSize.width / 2, winSize.height / 4));
    auto loginButtonImage = MenuItemImage::create("Images/Interface/LoginButton.png", "Images/Interface/LoginButton_selected.png", CC_CALLBACK_1(MainScene::menuCallback1, this));
    auto loginMenu = Menu::create(loginButtonImage, NULL);
    loginScene->setScaleX(0.7f);
    loginScene->setScaleY(0.5f);
    loginMenu->setPosition(Vec2(winSize.width * 5 / 8 - 30, winSize.height / 4 - 40));
    loginMenu->alignItemsVertically();
    loginMenu->setAnchorPoint(Vec2(0, 0));
    loginMenu->setScaleX(0.7f);
    loginMenu->setScaleY(0.5f);
    this->addChild(loginScene);
    this->addChild(loginMenu);
    
    // Login입력 받는 box 구현
    m_LoginBox = InputBox::create("이름을 입력", "Thonburi", MAX_NAME_LEN);
    m_LoginBox->setColor(Color3B::BLACK);
    m_LoginBox->beginInput();
    m_LoginBox->setFontSize(25.0f);
    m_LoginBox->setPosition(Vec2(winSize.width / 2 - 10, winSize.height / 4));
    this->addChild(m_LoginBox);

    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/mainscene.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);

    return true;
}

void MainScene::menuCallback1(Ref* sender)
{
    LoginToServer();
}
void MainScene::menuCallback2(Ref* sender)
{
    Director::getInstance()->end();
}

void MainScene::ConnectLabelCreate(const char* str, MainScene* scene)
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

void MainScene::ConnectLabelChange(const char* str)
{
    auto label = GET_CONNECT_LABEL;
    if (label != nullptr)
    {
        label->setString(str);
    }
}

void MainScene::LoginToServer()
{
    m_LoginName = m_LoginBox->getString();
    if (m_LoginName[0] == '\0' || m_LoginName[0] == ' ') // Name맨앞 공백 혹은 안썼을 때 return
    {
        m_LoginBox->clear();
        m_LoginBox->beginInput();
        return;
    }

    if (TcpClient::getInstance()->checkSocket() != NULL)
    {
        m_LoginBox->clear();
        m_LoginBox->beginInput();
        return;
    }

    ConnectLabelCreate("로그인 시도 중......", this);
    if (TcpClient::getInstance()->connect() == false)
    {
        TcpClient::getInstance()->disconnect();
        GET_CONNECT_LABEL->setString("로그인 실패.");
        m_LoginBox->clear();
        m_LoginBox->beginInput();
        return;
    }
    m_LoginBox->endInput();
    auto scene = NetworkScene::createScene();
    Director::getInstance()->pushScene(scene);
    TcpClient::getInstance()->loginRequest(m_LoginName.c_str());
}
