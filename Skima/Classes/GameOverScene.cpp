#include "pch.h"
#include "GameOverScene.h"
#include "NetworkScene.h"
#include "TcpClient.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene* GameOverScene::createScene(RoomInfo roomInfo, int playerId, bool isWin)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	auto scene = Scene::create();
	auto layer = GameOverScene::create();
    Sprite* endScene;
	scene->addChild(layer, 0, "GameOverScene");
	layer->SetRoomInfo(roomInfo);

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Background/winner.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Background/loser.mp3");

    if (isWin)
    {
        endScene = Sprite::create("Images/Background/WinScene.png");
        SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/winner.mp3");

    }
	else
	{
        endScene = Sprite::create("Images/Background/LoseScene.png");
        SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/loser.mp3");

	}
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
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
	//auto label1 = Label::createWithSystemFont("Play Again", "Thonburi", 50);
	auto label2 = Label::createWithSystemFont("Exit", "Thonburi", 50);

	//auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(GameOverScene::menuCallback1, this));
	auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(GameOverScene::menuCallback2, this));

	auto menu = Menu::create(menuItem2, NULL);
	menu->alignItemsVertically();
	menu->setPositionY(250);
	this->addChild(menu, 2, "GameOverMenu");

	return true;
}
// 
// void GameOverScene::menuCallback1(Ref* sender)	// 게임 시작
// {
//     SimpleAudioEngine::getInstance()->stopBackgroundMusic();
// 
// 	Director::getInstance()->popScene();
// }

void GameOverScene::menuCallback2(Ref* sender)	// 나가기
{
	if (TcpClient::getInstance()->checkSocket() != NULL)
		TcpClient::getInstance()->outRoomRequest(m_RoomInfo);

    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/Background/mainscene.mp3", true);

    Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}
