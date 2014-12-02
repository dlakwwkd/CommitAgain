#include "pch.h"
#include "MultiGameScene.h"
#include "GameOverScene.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "ListenerLayer.h"
#include "GameManager.h"
#include "UILayer.h"
#include "windows.h"

Scene* MultiGameScene::createScene()
{
	ShowCursor(false);
    auto scene = Scene::create();
	auto layer1 = MultiGameScene::create();
	auto layer2 = ListenerLayer::create();
	scene->addChild(layer1, 0, "MultiGameScene");
	layer1->addChild(layer2, 0, "ListenerLayer");
	return scene;
}


bool MultiGameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	GET_GM.SetGameMode(MULTI);
	m_IsStartGame = false;

	auto layer1 = LoadingBGLayer::create();
	auto layer2 = UILayer::create();
	this->addChild(layer1, 10, "LoadingBGLayer");
	this->addChild(layer2, 5, "UILayer");
	
	return true;
}

void MultiGameScene::StartGame()
{
	RemoveLoadingLayer();
    ShowCursor(false);
	m_IsStartGame = true;
}

void MultiGameScene::RemoveLoadingLayer()
{
	this->removeChildByName("LoadingBGLayer");
}

void MultiGameScene::GameOver(int playerId, int loseId)
{
// 	auto scene = GameOverScene::createScene();
// 	Director::getInstance()->popScene();
// 	Director::getInstance()->pushScene(scene);
}
