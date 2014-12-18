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

    auto label1 = Label::createWithSystemFont("싱글 플레이", "Thonburi", 50);
    auto label2 = Label::createWithSystemFont("멀티 플레이", "Thonburi", 50);
    auto label3 = Label::createWithSystemFont("게임 종료", "Thonburi", 50);

    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(MainScene::menuCallback1, this));
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(MainScene::menuCallback2, this));
    auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(MainScene::menuCallback3, this));

    auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu, 0, "MainMenu");
    return true;
}

void MainScene::menuCallback1(Ref* sender)
{
}
void MainScene::menuCallback2(Ref* sender)
{
    auto scene = NetworkScene::createScene();
    Director::getInstance()->pushScene(scene);
}
void MainScene::menuCallback3(Ref* sender)
{
    Director::getInstance()->end();
}

