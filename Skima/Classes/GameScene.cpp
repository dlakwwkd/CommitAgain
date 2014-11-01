#include "GameScene.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "MapLayer.h"
#include "ObjectLayer.h"
//#include "UILayer.h"

Scene* GameScene::createScene()
{
	
 	auto scene = Scene::createWithPhysics();

	//수정필요
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
 	scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto layer = GameScene::create();

	auto physLayer = PhysicsLayer::create();
	//	auto mapLayer = MapLayer::create();
	//	auto objectLayer = ObjectLayer::create();

	auto loadingBGLayer = LoadingBGLayer::create();

//	layer2->SetPhyWorld(scene->getPhysicsWorld());

	//수정필요

	
	scene->addChild(layer, 0, "GameScene");
	layer->addChild(loadingBGLayer, 5, "LoadingBGLayer");
// 	layer->addChild(mapLayer, 0, "MapLayer");
// 	layer->addChild(objectLayer, 1, "ObjectLayer");

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

void GameScene::removeLoading()
{

	// this??
	this->removeChildByName("LoadingBGLayer");
}

// void GameScene::popupLoading()
// {
// 	auto loadingBGLayer = LoadingBGLayer::create();
// 	loadingBGLayer->setOpacity(128); //반투명
// 	

