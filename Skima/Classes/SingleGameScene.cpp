#include "pch.h"
#include "SingleGameScene.h"
#include "GameManager.h"
#include "PhysicsLayer.h"
#include "ObjectLayer.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "UILayer.h"

Scene* SingleGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto layer1 = SingleGameScene::create();
	auto layer2 = PhysicsLayer::create();

	layer2->SetPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer1, 0, "SingleGameScene");
	layer1->addChild(layer2, 0, "PhysicsLayer");
	return scene;
}

bool SingleGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	GET_GM.SetGameMode(SINGLE);

	auto layer = UILayer::create();
	this->addChild(layer, 5, "UILayer");
	return true;
}