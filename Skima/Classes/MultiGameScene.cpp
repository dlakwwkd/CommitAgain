#include "pch.h"
#include "MultiGameScene.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "ListenerLayer.h"
#include "GameManager.h"

USING_NS_CC;

Scene* MultiGameScene::createScene()
{
    auto scene = Scene::create();
	auto layer = MultiGameScene::create();
	scene->addChild(layer, 0, "MultiGameScene");
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

	auto listenerLayer = ListenerLayer::create();
	auto loadingLayer = LoadingBGLayer::create();
	this->addChild(listenerLayer, 0, "ListenerLayer");
	this->addChild(loadingLayer, 10, "LoadingBGLayer");
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
