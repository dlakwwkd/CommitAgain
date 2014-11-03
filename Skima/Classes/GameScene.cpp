#include "GameScene.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
//#include "UILayer.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
 	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto layer = GameScene::create();
	auto layer2 = PhysicsLayer::create();
	layer2->SetPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer, 0, "GameScene");
	layer->addChild(layer2, 0, "PhysicsLayer");

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	return true;
}
