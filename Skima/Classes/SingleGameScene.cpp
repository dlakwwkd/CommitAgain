#include "SingleGameScene.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
//#include "UILayer.h"

Scene* SingleGameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SingleGameScene::create();
	scene->addChild(layer, 0, "SingleGameScene");
	return scene;
}

bool SingleGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto layer = PhysicsLayer::create();
	this->addChild(layer, 0, "PhysicsLayer");

	return true;
}