#include "RoomScene.h"
#include "GameScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"


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

	auto label1 = Label::createWithSystemFont("게임 시작", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("나가기", "Thonburi", 50);

	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(RoomScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(RoomScene::menuCallback2, this));

	auto menu = Menu::create(menuItem1, menuItem2, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 0, "RoomMenu");

	return true;
}

void RoomScene::menuCallback1(Ref* sender)
{
	//소켓연결확인
	if (TcpClient::getInstance()->checkSocket() == NULL)
		return;

	// 게임스타트 요청 패킷보내기
	TcpClient::getInstance()->gameStartRequest();

	
	
}
void RoomScene::menuCallback2(Ref* sender)
{
	if (TcpClient::getInstance()->checkSocket() == NULL)
		return;

	TcpClient::getInstance()->outRoomRequest(m_RoomID);

	Director::getInstance()->popScene();
}


void RoomScene::makeRoomComplete(int roomId)
{
	m_RoomID = roomId;

	CCLOG("room!!!!!!!!!!!");

}

void RoomScene::gameStartComplete()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);
	


}
