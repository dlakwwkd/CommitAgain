#include "pch.h"
#include "MainScene.h"
#include "NetworkScene.h"

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

    auto textField = TextFieldTTF::textFieldWithPlaceHolder("이름을 입력해주세요.", Size(480, 30), kCCTextAlignmentCenter, "Arial", 20);
    textField->setPosition(Vec2(winSize.width / 2 - 10, winSize.height * 3 / 8));
    textField->attachWithIME();
    textField->setTextColor(Color4B::BLACK);
    this->addChild(textField, 1);

    return true;
}

void MainScene::menuCallback1(Ref* sender)
{
    auto scene = NetworkScene::createScene();
    Director::getInstance()->pushScene(scene);
}
void MainScene::menuCallback2(Ref* sender)
{
    Director::getInstance()->end();
}

