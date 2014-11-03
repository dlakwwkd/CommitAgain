#include "NetworkGameScene.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
#include "ListenerLayer.h"

USING_NS_CC;

Scene* NetworkGameScene::createScene()
{
    auto scene = Scene::create();
	auto layer = NetworkGameScene::create();
	scene->addChild(layer, 0, "NetworkGameScene");
    return scene;
}


bool NetworkGameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	m_IsStartGame = false;

	auto listenerLayer = ListenerLayer::create();
	auto loadingLayer = LoadingBGLayer::create();
	this->addChild(listenerLayer, 0, "ListenerLayer");
	this->addChild(loadingLayer, 10, "LoadingBGLayer");
}

void NetworkGameScene::StartGame()
{
	RemoveLoadingLayer();
	m_IsStartGame = true;
}

void NetworkGameScene::RemoveLoadingLayer()
{
	this->removeChildByName("LoadingBGLayer");
}
