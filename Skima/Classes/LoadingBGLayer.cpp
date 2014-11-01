#include "LoadingBGLayer.h"


bool LoadingBGLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,0))) //검은색 세팅
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize(); //사이즈 지정

	auto loadingLabel = Label::createWithSystemFont("로딩중...", "Thonburi", 50, Size(250,150), TextHAlignment::LEFT);

	


	return true;
}
