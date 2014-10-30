#include "UILayer.h"


bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto menuItem1 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(UILayer::doClick1, this));

	auto menu = Menu::create(menuItem1, NULL);

	menu->alignItemsVertically();

	this->addChild(menu);

	return true;
}

void UILayer::doClick1(Ref* sender)
{
	Director::getInstance()->popScene();
}
