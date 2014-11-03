#include "LoadingBGLayer.h"


bool LoadingBGLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,0))) //검은색 세팅
	{
		return false;
	}
	this->setOpacity(210);


	auto loadinglabel = LabelTTF::create("Loading...", "Arial", 50);
	loadinglabel->setPosition(500, 400);
	this->addChild(loadinglabel);



	return true;
}
