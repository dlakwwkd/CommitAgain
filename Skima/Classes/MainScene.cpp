#include "MainScene.h"


Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{

	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}
	
	auto menuItem1 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(MainScene::doClick1, this));

	auto menuItem2 = MenuItemImage::create(
		"Images/btn-highscores-normal.png",
		"Images/btn-highscores-selected.png",
		this,
		menu_selector(MainScene::doClick2));

	auto menuItem3 = MenuItemImage::create(
		"Images/btn-about-normal.png",
		"Images/btn-about-selected.png",
		this,
		menu_selector(MainScene::doClick3));

	auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);

	menu->alignItemsVertically();

	this->addChild(menu);

	return true;
}

void MainScene::doClick1(Ref* sender)
{
	log("메뉴1");
}

void MainScene::doClick2(Ref* sender)
{
	log("메뉴2");

}

void MainScene::doClick3(Ref* sender)
{
	log("메뉴3");

}
