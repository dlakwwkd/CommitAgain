#include "GameScene.h"
#include "PhysicsLayer.h"
#include "UILayer.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto layer = GameScene::create();
	auto layer2 = PhysicsLayer::create();
	layer2->setPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer, 0, "GameScene");
	layer->addChild(layer2, 0, "PhyshicsLayer");

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto layer = UILayer::create();
	this->addChild(layer, 10, "UILayer");

	return true;
}