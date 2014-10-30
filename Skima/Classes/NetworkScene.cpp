#include "NetworkScene.h"
#include "GameScene.h"
#include "TcpClient.h"
#include "Enums.h"


Scene* NetworkScene::createScene()
{
	auto scene = Scene::create();
	auto layer = NetworkScene::create();
	scene->addChild(layer, 0, "Network Layer");
	return scene;
}

bool NetworkScene::init()
{
	if (!LayerColor::initWithColor(Color4B(100,100,200,255)))
	{
		return false;
	}

	m_PlayerID = -1;
	m_RoomID = -1;
	m_GameID = -1;
	
	TcpClient::getInstance()->loginRequest();
	auto label = Label::createWithSystemFont("立加 吝...", "Thonburi", 50);
	label->setAnchorPoint(Point::ZERO);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(label, 0, "Connect Label");
	
	auto label1 = Label::createWithSystemFont("规 积己", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("规 曼咯", "Thonburi", 50);
	auto label3 = Label::createWithSystemFont("唱啊扁", "Thonburi", 50);

	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(NetworkScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(NetworkScene::menuCallback2, this));
	auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(NetworkScene::menuCallback3, this));

	auto menu = Menu::create(menuItem1, menuItem2, menuItem3, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 0, "Network Menu");

	return true;
}

void NetworkScene::menuCallback1(Ref* sender)
{


}
void NetworkScene::menuCallback2(Ref* sender)
{


}
void NetworkScene::menuCallback3(Ref* sender)
{
	TcpClient::destroyInstance();
	Director::getInstance()->popScene();
}

