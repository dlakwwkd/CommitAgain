#include "pch.h"
#include "GameOverScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "MultiGameScene.h"

Scene* GameOverScene::createScene(int roomId, int playerId, int loseId)
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer, 0, "GameOverScene");
	layer->SetRoomID(roomId);

	char* strResult;

	if (playerId != loseId)
	{
		strResult = "WIN!!";
	}
	else
	{
		strResult = "Lose...";
	}

	auto label = Label::createWithSystemFont(strResult, "Thonburi", 150);
	label->setPosition(Point(650, 500));
	layer->addChild(label);
	return scene;
}

bool GameOverScene::init()
{
	ShowCursor(true);

	if (!LayerColor::initWithColor(Color4B(100, 100, 200, 255)))
	{
		return false;
	}

	auto label1 = Label::createWithSystemFont("재시작", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("나가기", "Thonburi", 50);

	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(GameOverScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(GameOverScene::menuCallback2, this));

	auto menu = Menu::create(menuItem1, menuItem2, NULL);
	menu->alignItemsVertically();
	menu->setPositionY(300);
	this->addChild(menu, 0, "GameOverMenu");
}

void GameOverScene::menuCallback1(Ref* sender)	// 게임 시작
{
	Director::getInstance()->popScene();
}

void GameOverScene::menuCallback2(Ref* sender)	// 나가기
{
	if (TcpClient::getInstance()->checkSocket() != NULL)
		TcpClient::getInstance()->outRoomRequest(m_RoomId);

	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}
