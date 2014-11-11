#include "pch.h"
#include "NetworkScene.h"
#include "SingleGameScene.h"
#include "RoomScene.h"
#include "TcpClient.h"

#define GET_CONNECT_LABEL dynamic_cast<Label*>(this->getChildByName("ConnectLabel"))

Scene* NetworkScene::createScene()
{
	auto scene = Scene::create();
	auto layer = NetworkScene::create();
	scene->addChild(layer, 0, "NetworkScene");
	return scene;
}

bool NetworkScene::init()
{
	if (!LayerColor::initWithColor(Color4B(100, 100, 200, 255)))
	{
		return false;
	}
	
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

	// 3�� ���� Tick �Լ��� ȣ���Ѵ�.
	this->schedule(schedule_selector(NetworkScene::Tick), 3.0f);
	return true;
}

void NetworkScene::menuCallback0(Ref* sender)	// ���� ����
{
	if (TcpClient::getInstance()->checkSocket() != NULL)
		return;

	ConnectLabelCreate("������ ���� ��......", this);
	if (TcpClient::getInstance()->connect() == false)
	{
		TcpClient::getInstance()->disconnect();
		GET_CONNECT_LABEL->setString("���� ���� ����.");
		return;
	}
	TcpClient::getInstance()->loginRequest();
}

void NetworkScene::menuCallback1(Ref* sender)	// �� ����
{
	if (TcpClient::getInstance()->checkSocket() == NULL)
		return;

	ConnectLabelChange("�� ���� ��...");
	TcpClient::getInstance()->makeRoomRequest();	
}

void NetworkScene::menuCallback2(Ref* sender)	// �� ����
{
	if (TcpClient::getInstance()->checkSocket() == NULL)
		return;

	ConnectLabelChange("�濡 ���� ��...");
	TcpClient::getInstance()->joinRoomRequest();
}

void NetworkScene::menuCallback3(Ref* sender)	// ������
{
	TcpClient::getInstance()->disconnect();
	Director::getInstance()->popScene();
}



//////////////////////////////////////////////////////////////////////////
void NetworkScene::Tick(float dt)
{
	if (TcpClient::getInstance()->checkSocket() == NULL)
		ConnectLabelChange("���� ���� ����.");
	else
		ConnectLabelChange("���� ���� ��ȣ.");
}
//////////////////////////////////////////////////////////////////////////



void NetworkScene::ConnectLabelCreate(const char* str, NetworkScene* scene)
{
	if (scene->getChildByName("ConnectLabel") != nullptr)
	{
		scene->removeChildByName("ConnectLabel");
	}
	auto label = Label::createWithSystemFont(str, "Thonburi", 50);
	label->setAnchorPoint(Point::ZERO);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	scene->addChild(label, 0, "ConnectLabel");
}

void NetworkScene::ConnectLabelChange(const char* str)
{
	auto label = GET_CONNECT_LABEL;
	if (label != nullptr)
		label->setString(str);
}

void NetworkScene::MakeRoomComplete(int roomId)
{
	ConnectLabelChange("���� ���� ��ȣ.");
	auto scene = RoomScene::createScene();
	auto layer = dynamic_cast<RoomScene*>(scene->getChildByName("RoomScene"));
	layer->SetRoomID(roomId);
	Director::getInstance()->pushScene(scene);
}

void NetworkScene::JoinRoomComplete(int roomId)
{
	ConnectLabelChange("���� ���� ��ȣ.");
	auto scene = RoomScene::createScene();
	auto layer = dynamic_cast<RoomScene*>(scene->getChildByName("RoomScene"));
	layer->SetRoomID(roomId);
	Director::getInstance()->pushScene(scene);
}


