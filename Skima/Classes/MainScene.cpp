#include "pch.h"
#include "MainScene.h"
#include "NetworkScene.h"
#include "RoomScene.h"
#include "InputBox.h"
#include "TcpClient.h"


#define MAX_NAME_LEN 14
#define GET_CONNECT_LABEL dynamic_cast<Label*>(this->getChildByName("ConnectLabel"))

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer, 0, "MainScene");
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 배경화면 plist 보여주는 부분
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_01.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_02.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_03.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_04.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_05.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_06.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_07.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_08.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_09.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MainBackground_10.plist");

    auto background = Sprite::createWithSpriteFrameName("MainBackground_001.png");
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.2f);

    for (int i = 1; i <= 196; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("MainBackground_%003d.png", i));
        animation->addSpriteFrame(frame);
    }
    background->runAction(RepeatForever::create(Animate::create(animation)));
    background->setScaleX(2.70f);
    background->setScaleY(2.30f);
    background->setAnchorPoint(Vec2::ZERO);
    this->addChild(background);

    // Login창 띄우기
    auto winSize = Director::getInstance()->getWinSize();
    auto loginScene = Sprite::create("Images/LoginScene.png");
    loginScene->setPosition(Vec2(winSize.width / 2, winSize.height * 3 / 8));
    auto loginButtonImage = MenuItemImage::create("Images/LoginButton.png", "Images/LoginButton_selected.png", CC_CALLBACK_1(MainScene::menuCallback1, this));
    auto loginMenu = Menu::create(loginButtonImage, NULL);
    loginScene->setScaleX(0.7f);
    loginScene->setScaleY(0.5f);
    loginMenu->setPosition(Vec2(winSize.width * 5 / 8 - 30, winSize.height * 3 / 8 - 40));
    loginMenu->alignItemsVertically();
    loginMenu->setAnchorPoint(Vec2(0, 0));
    loginMenu->setScaleX(0.7f);
    loginMenu->setScaleY(0.5f);
    this->addChild(loginScene);
    this->addChild(loginMenu);
    
    // Login입력 받는 box 구현
    m_LoginBox = InputBox::create("이름을 입력해주세요", "Thonburi", MAX_NAME_LEN);
    m_LoginBox->setColor(Color3B::BLACK);
    m_LoginBox->beginInput();
    m_LoginBox->setFontSize(25.0f);
    m_LoginBox->setPosition(Vec2(winSize.width / 2 - 10, winSize.height * 3 / 8));
    this->addChild(m_LoginBox);

    return true;
}

void MainScene::menuCallback1(Ref* sender)
{
    m_LoginName = m_LoginBox->getString();

    if (TcpClient::getInstance()->checkSocket() != NULL)
        return;

    ConnectLabelCreate("로그인 시도 중......", this);
    if (TcpClient::getInstance()->connect() == false)
    {
        TcpClient::getInstance()->disconnect();
        GET_CONNECT_LABEL->setString("로그인 실패.");
        m_LoginBox->clear();
        m_LoginBox->beginInput();
        return;
    }
    auto scene = NetworkScene::createScene();
    Director::getInstance()->pushScene(scene);
    TcpClient::getInstance()->loginRequest(m_LoginName.c_str());
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
