#include "SingleGameScene.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
//#include "UILayer.h"

Scene* SingleGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto layer = SingleGameScene::create();
	auto layer2 = PhysicsLayer::create();

	layer2->SetPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer, 0, "SingleGameScene");
	layer->addChild(layer2, 0, "PhysicsLayer");
	return scene;
}

bool SingleGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}