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
    auto scene = Scene::create();
    auto layer1 = GameScene::create();
    auto layer2 = ListenerLayer::create();
    scene->addChild(layer1, 3, GAME_SCENE);
    layer1->addChild(layer2, 0, LISTENER_LAYER);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
        return false;

    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/game2.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.00001f);
    m_IsStartGame = false;

    auto layer1 = LoadingBGLayer::create();
    auto layer2 = UILayer::create();
    auto layer3 = EscLayer::create();
    this->addChild(layer1, 3, LOADING_LAYER);
    this->addChild(layer2, 1, UI_LAYER);
    this->addChild(layer3, 2, ESC_LAYER);
    layer3->setVisible(false);
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
    this->removeChildByName(LOADING_LAYER);
}

void GameScene::GameOver(int playerId, bool isWin)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    m_IsStartGame = false;

    auto scene = GameOverScene::createScene(m_RoomInfo, playerId, isWin);
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(scene);
}
