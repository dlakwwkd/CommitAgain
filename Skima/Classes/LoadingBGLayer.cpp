#include "LoadingBGLayer.h"


bool LoadingBGLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,0))) //������ ����
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize(); //������ ����

	auto loadingLabel = Label::createWithSystemFont("�ε���...", "Thonburi", 50, Size(250,150), TextHAlignment::LEFT);

	


	return true;
}
