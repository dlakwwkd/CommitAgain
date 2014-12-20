#include "pch.h"
#include "GameOverScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "GameScene.h"

Scene* GameOverScene::createScene(int roomId, int playerId, int loseId)
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
    Sprite* endScene;
	scene->addChild(layer, 0, "GameOverScene");
	layer->SetRoomID(roomId);

    if (playerId != loseId)
    {
        endScene = Sprite::create("Images/WinScene.png");
    }
	else
	{
        endScene = Sprite::create("Images/LoseScene.png");
	}
    endScene->setAnchorPoint(Vec2(0, 0));
    endScene->setZOrder(1);

    layer->addChild(endScene);
	return scene;
}

bool GameOverScene::init()
{
	if (!LayerColor::initWithColor(Color4B(100, 100, 200, 255)))
	{
		return false;
	}
	ShowCursor(true);
	auto label1 = Label::createWithSystemFont("Play Again", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("Exit", "Thonburi", 50);

	auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(GameOverScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(GameOverScene::menuCallback2, this));

	auto menu = Menu::create(menuItem1, menuItem2, NULL);
	menu->alignItemsVertically();
	menu->setPositionY(200);
	this->addChild(menu, 2, "GameOverMenu");

	return true;
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
