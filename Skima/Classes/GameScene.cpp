#include "pch.h"
#include "GameScene.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "ListenerLayer.h"
#include "GameManager.h"
#include "UILayer.h"
#include "windows.h"
#include "GameOverScene.h"
#include "EscLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene* GameScene::createScene()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    auto scene = Scene::create();
    auto layer1 = GameScene::create();
    auto layer2 = ListenerLayer::create();
    scene->addChild(layer1, 3, "GameScene");
    layer1->addChild(layer2, 0, "ListenerLayer");

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Background/game1.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Background/game2.mp3");

    return scene;
}


bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    m_IsStartGame = false;

    auto layer1 = LoadingBGLayer::create();
    auto layer2 = UILayer::create();
    auto layer3 = EscLayer::create();
    this->addChild(layer1, 10, "LoadingBGLayer");
    this->addChild(layer2, 5, "UILayer");
    this->addChild(layer3, 20, "EscLayer");
    layer3->setVisible(false);
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/game2.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.00001f);

    return true;
}

void GameScene::StartGame()
{
    RemoveLoadingLayer();
    ShowCursor(false);
    m_IsStartGame = true;
}

void GameScene::RemoveLoadingLayer()
{
    this->removeChildByName("LoadingBGLayer");
}

void GameScene::GameOver(int playerId, int loseId)
{
    m_IsStartGame = false;
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    auto scene = GameOverScene::createScene(m_RoomId, playerId, loseId);
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(scene);
}
