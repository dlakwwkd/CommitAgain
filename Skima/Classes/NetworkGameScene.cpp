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
	auto listenerLayer = ListenerLayer::create();

	scene->addChild(layer,0,"NetworkGameScene");
	layer->addChild(listenerLayer, 0, "ListenerLayer");

    return scene;
}


bool NetworkGameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto loadingLayer = LoadingBGLayer::create();
	this->addChild(loadingLayer, 10,"LoadingLayer");


// 	Size winsize = Director::getInstance()->getWinSize();
// 	auto bg = Sprite::create("bg1.png");
// 	bg->setPosition(winsize.width / 2, winsize.height / 2);
// 	this->addChild(bg,0);
//  
// 	auto bgLayer = BGLayer::create();
// 	auto charlayer = CharacterLayer::create();
// 	this->addChild(bgLayer,5);
// 	this->addChild(charlayer, 1);

	

}

void NetworkGameScene::removeLoadingLayer()
{
	this->removeChildByName("LoadingBGLayer");

}
