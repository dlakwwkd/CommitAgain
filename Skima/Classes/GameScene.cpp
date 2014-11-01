#include "GameScene.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
//#include "UILayer.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto layer = GameScene::create();
	auto layer2 = PhysicsLayer::create();
	auto loadingBGLayer = LoadingBGLayer::create();
	

	layer2->SetPhyWorld(scene->getPhysicsWorld());

	
	scene->addChild(layer, 0, "GameScene");
	layer->addChild(loadingBGLayer, 5, "LoadingBGLayer");
	layer->addChild(layer2, 0, "PhyshicsLayer");

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

// void GameScene::popupLoading()
// {
// 	auto loadingBGLayer = LoadingBGLayer::create();
// 	loadingBGLayer->setOpacity(128); //π›≈ı∏Ì
// 	
}
