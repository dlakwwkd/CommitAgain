#include "MainScene.h"
#include "GameScene.h"
#include "NetworkScene.h"


Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer, 0, "MainScene");
	return scene;
}

bool MainScene::init()
{
	if (!LayerColor::initWithColor(Color4B(100, 100, 200, 255)))
	{
		return false;
	}

	auto label1 = Label::createWithSystemFont("�̱� �÷���", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("��Ƽ �÷���", "Thonburi", 50);
	auto label3 = Label::createWithSystemFont("���� ����", "Thonburi", 50);

	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(MainScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(MainScene::menuCallback2, this));
	auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(MainScene::menuCallback3, this));

	auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 0, "MainMenu");

	return true;
}

void MainScene::menuCallback1(Ref* sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void MainScene::menuCallback2(Ref* sender)
{
	auto scene = NetworkScene::createScene();
	Director::getInstance()->pushScene(scene);
}
void MainScene::menuCallback3(Ref* sender)
{
	Director::getInstance()->end();
}

