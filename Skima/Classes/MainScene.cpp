#include "pch.h"
#include "MainScene.h"
#include "NetworkScene.h"
#include "InputBox.h"
#include "TcpClient.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define MAX_NAME_LEN 14

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer, 0, MAIN_SCENE);
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init())
        return false;

    InitSound();
    InitBackground();
    auto winSize = Director::getInstance()->getWinSize();

    // Login 창
    auto loginBox = MenuItemImage::create(
        "Images/Interface/LoginScene.png",
        "Images/Interface/LoginScene.png",
        CC_CALLBACK_1(MainScene::menuCallback1, this));

    auto loginMenu1 = Menu::create(loginBox, NULL);
    loginMenu1->setPosition(Vec2(winSize.width / 2, winSize.height / 4));
    this->addChild(loginMenu1);

    // Login 버튼
    auto loginButton = MenuItemImage::create(
        "Images/Interface/LoginButton.png",
        "Images/Interface/LoginButton_selected.png",
        CC_CALLBACK_1(MainScene::menuCallback2, this));

    auto loginMenu2 = Menu::create(loginButton, NULL);
    loginMenu2->setPosition(Vec2(415, 35));
    loginBox->addChild(loginMenu2);

    // Login 입력박스
    m_LoginBox = InputBox::create(LOGIN_BOX_INIT_TEXT, DEF_FONT, MAX_NAME_LEN);
    m_LoginBox->setAnchorPoint(Vec2(1,0));
    m_LoginBox->setPosition(Vec2(320, 92));
    m_LoginBox->setColor(Color3B::BLACK);
    m_LoginBox->setFontSize(25);
    loginBox->addChild(m_LoginBox);
    return true;
}

void MainScene::menuCallback1(Ref* sender)
{
    m_LoginBox->clear();
    m_LoginBox->beginInput();
}

void MainScene::menuCallback2(Ref* sender)
{
    LoginToServer();
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

    ConnectLabelCreate(TRY_CONNECT_TEXT, this);
    if (TcpClient::getInstance()->connect() == false)
    {
        TcpClient::getInstance()->disconnect();
        ConnectLabelChange(CONNECT_FAILED_TEXT);
        m_LoginBox->clear();
        m_LoginBox->beginInput();
        return;
    }
    m_LoginBox->endInput();

    auto scene = NetworkScene::createScene();
    Director::getInstance()->pushScene(scene);
    TcpClient::getInstance()->loginRequest(m_LoginName.c_str());
}



void MainScene::ConnectLabelCreate(const char* str, MainScene* scene)
{
    if (scene->getChildByName(CONNECT_LABEL) != nullptr)
        scene->removeChildByName(CONNECT_LABEL);

    auto label = Label::createWithSystemFont(str, DEF_FONT, 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    scene->addChild(label, 0, CONNECT_LABEL);
}

void MainScene::ConnectLabelChange(const char* str)
{
    auto label = dynamic_cast<Label*>(this->getChildByName(CONNECT_LABEL));
    if (label != nullptr)
        label->setString(str);
}

void MainScene::InitBackground()
{
    auto winSize = Director::getInstance()->getWinSize();
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_01.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_02.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_03.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_04.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_05.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_06.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_07.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_08.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_09.plist");
    cache->addSpriteFramesWithFile("Images/Background/MainBackground_10.plist");

    auto ani = Animation::create();
    ani->setDelayPerUnit(0.12f);
    for (int i = 1; i <= 196; ++i)
    {
        ani->addSpriteFrame(cache->getSpriteFrameByName(StringUtils::format("MainBackground_%003d.png", i)));
    }
    auto bg1 = Sprite::createWithSpriteFrameName("MainBackground_001.png");
    bg1->setAnchorPoint(Vec2::ZERO);
    bg1->setScaleX(3.6f);
    bg1->setScaleY(3.0f);
    bg1->runAction(RepeatForever::create(Animate::create(ani)));

    auto bg2 = Sprite::create("Images/Background/MainBackground2.png");
    bg2->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    bg2->setOpacity(50);

    auto title = Sprite::create("Images/Background/SkimaTitle.png");
    title->setPosition(Vec2(winSize.width / 2, winSize.height * 3 / 4));
    title->setScale(1.3f);

    this->addChild(bg1);
    this->addChild(bg2);
    this->addChild(title);
}

void MainScene::InitSound()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("Music/Background/mainscene.mp3");
    audio->preloadBackgroundMusic("Music/Background/banpick.mp3");
    audio->preloadBackgroundMusic("Music/Background/game2.mp3");
    audio->preloadBackgroundMusic("Music/Background/winner.mp3");
    audio->preloadBackgroundMusic("Music/Background/loser.mp3");
    audio->preloadEffect("Music/Effect/buff_on.mp3");
    audio->preloadEffect("Music/Effect/crash.mp3");
    audio->preloadEffect("Music/Effect/damage.mp3");
    audio->preloadEffect("Music/Effect/dash.wav");
    audio->preloadEffect("Music/Effect/explode.mp3");
    audio->preloadEffect("Music/Effect/fireballshoot.mp3");
    audio->preloadEffect("Music/Effect/firewall.mp3");
    audio->preloadEffect("Music/Effect/flash.mp3");
    audio->preloadEffect("Music/Effect/hide.mp3");
    audio->preloadEffect("Music/Effect/iceballshoot.mp3");
    audio->preloadEffect("Music/Effect/lightningshoot.mp3");
    audio->preloadEffect("Music/Effect/meteor_hit.mp3");
    audio->preloadEffect("Music/Effect/meteor_shoot.mp3");
    audio->preloadEffect("Music/Effect/mobdied.mp3");
    audio->preloadEffect("Music/Effect/rockcrash.mp3");
    audio->preloadEffect("Music/Effect/shield.mp3");
    audio->preloadEffect("Music/Effect/shield_off.mp3");
    audio->preloadEffect("Music/Effect/swipe.mp3");
    audio->preloadEffect("Music/Effect/teleport.wav");
    audio->preloadEffect("Music/Effect/thunder.mp3");

    audio->playBackgroundMusic("Music/Background/mainscene.mp3", true);
    audio->setBackgroundMusicVolume(1.0f);
}
