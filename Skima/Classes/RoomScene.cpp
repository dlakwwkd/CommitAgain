#include "RoomScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "MultiGameScene.h"


Scene* RoomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RoomScene::create();
	scene->addChild(layer, 0, "RoomScene");
	return scene;
}

bool RoomScene::init()
{
	if (!LayerColor::initWithColor(Color4B(100, 100, 200, 255)))
	{
		return false;
	}

	m_RoomID = -1;

	auto label1 = Label::createWithSystemFont("���� ����", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("������", "Thonburi", 50);

	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(RoomScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(RoomScene::menuCallback2, this));

	auto menu = Menu::create(menuItem1, menuItem2, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 0, "RoomMenu");


	auto label = Label::createWithSystemFont("���� ��...", "Thonburi", 50);
	label->setAnchorPoint(Point::ZERO);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(label, 0, "RoomStateLabel");

	// 1�� ���� Tick �Լ��� ȣ���Ѵ�.
	this->schedule(schedule_selector(RoomScene::Tick), 1.0f);
	return true;
}

void RoomScene::menuCallback1(Ref* sender) //"���ӽ���"
{
	//���Ͽ���Ȯ��
	if (TcpClient::getInstance()->checkSocket() == NULL)
		return;

	// ���ӽ�ŸƮ ��û ��Ŷ������
	TcpClient::getInstance()->startGameRequest();

	
	
}
void RoomScene::menuCallback2(Ref* sender)	//"������"
{
	if (TcpClient::getInstance()->checkSocket() != NULL)
		TcpClient::getInstance()->outRoomRequest(m_RoomID);

	Director::getInstance()->popScene();
}


//////////////////////////////////////////////////////////////////////////
void RoomScene::Tick(float dt)
{
	auto label = dynamic_cast<Label*>(this->getChildByName("RoomStateLabel"));
	if (label == nullptr)
		return;

	// �� ��ȣ�� ���ڿ��� ��ȯ �� �󺧿� ����
	char buf[32];
	_itoa(m_RoomID, buf, 32);
	std::string roomNum = buf;
	roomNum += "�� ��";
	label->setString(roomNum.c_str());
}
//////////////////////////////////////////////////////////////////////////

void RoomScene::GameStartComplete()
{
	auto scene = MultiGameScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);
}
