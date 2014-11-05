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

	auto label1 = Label::createWithSystemFont("게임 시작", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("나가기", "Thonburi", 50);

	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(RoomScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(RoomScene::menuCallback2, this));

	auto menu = Menu::create(menuItem1, menuItem2, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 0, "RoomMenu");


	auto label = Label::createWithSystemFont("연결 중...", "Thonburi", 50);
	label->setAnchorPoint(Point::ZERO);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	this->addChild(label, 0, "RoomStateLabel");

	// 1초 마다 Tick 함수를 호출한다.
	this->schedule(schedule_selector(RoomScene::Tick), 1.0f);
	return true;
}

void RoomScene::menuCallback1(Ref* sender) //"게임시작"
{
	//소켓연결확인
	if (TcpClient::getInstance()->checkSocket() == NULL)
		return;

	// 게임스타트 요청 패킷보내기
	TcpClient::getInstance()->startGameRequest();

	
	
}
void RoomScene::menuCallback2(Ref* sender)	//"나가기"
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

	// 방 번호를 문자열로 변환 후 라벨에 적용
	char buf[32];
	_itoa(m_RoomID, buf, 32);
	std::string roomNum = buf;
	roomNum += "번 방";
	label->setString(roomNum.c_str());
}
//////////////////////////////////////////////////////////////////////////

void RoomScene::GameStartComplete()
{
	auto scene = MultiGameScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);
}
