#include "pch.h"
#include "MultiGameScene.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "ListenerLayer.h"
#include "GameManager.h"
#include "UILayer.h"

USING_NS_CC;

Scene* MultiGameScene::createScene()
{
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
}

void MultiGameScene::StartGame()
{
	RemoveLoadingLayer();
	m_IsStartGame = true;
}

void MultiGameScene::RemoveLoadingLayer()
{
	this->removeChildByName("LoadingBGLayer");
}
