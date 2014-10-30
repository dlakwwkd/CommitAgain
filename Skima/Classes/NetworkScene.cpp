#include "NetworkScene.h"
#include "GameScene.h"
#include "RoomScene.h"
#include "TcpClient.h"


Scene* NetworkScene::createScene()
{
	auto scene = Scene::create();
	auto layer = NetworkScene::create();
	scene->addChild(layer, 0, "NetworkScene");
	return scene;
}

bool NetworkScene::init()
{
	if (!LayerColor::initWithColor(Color4B(100,100,200,255)))
	{
		return false;
	}

	m_GameID = -1;
	
	auto label0 = Label::createWithSystemFont("���� ����", "Thonburi", 50);
	auto label1 = Label::createWithSystemFont("�� ����", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("�� ����", "Thonburi", 50);
	auto label3 = Label::createWithSystemFont("������", "Thonburi", 50);

	auto menuItem0 = MenuItemLabel::create(label0, CC_CALLBACK_1(NetworkScene::menuCallback0, this));
	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(NetworkScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(NetworkScene::menuCallback2, this));
	auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(NetworkScene::menuCallback3, this));

	auto menu = Menu::create(menuItem0, menuItem1, menuItem2, menuItem3, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 0, "NetworkMenu");

	return true;
}

void NetworkScene::menuCallback0(Ref* sender)
{
	if (TcpClient::getInstance()->checkSocket() != NULL)
		return;

	if (this->getChildByName("ConnectLabel") != nullptr)
	{
		this->removeChildByName("ConnectLabel");
	}

	auto label = Label::createWithSystemFont("���� ��......", "Thonburi", 50);
	label->setAnchorPoint(Point::ZERO);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(label, 0, "ConnectLabel");

	if (TcpClient::getInstance()->connect() == false)
	{
		TcpClient::getInstance()->disconnect();
		label->setString("���� ����.");
		return;
	}

	TcpClient::getInstance()->loginRequest();
}

void NetworkScene::menuCallback1(Ref* sender)
{
	auto scene = RoomScene::createScene();
	Director::getInstance()->pushScene(scene);

	TcpClient::getInstance()->makeRoomRequest();
}

void NetworkScene::menuCallback2(Ref* sender)
{


}

void NetworkScene::menuCallback3(Ref* sender)
{
	TcpClient::getInstance()->disconnect();
	Director::getInstance()->popScene();
}


void NetworkScene::connectComplit()
{
	auto label = dynamic_cast<Label*>(this->getChildByName("ConnectLabel"));
	if (label == nullptr)
		return;
	label->setString("���� �Ϸ�.");
}
