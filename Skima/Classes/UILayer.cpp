#include "pch.h"
#include "UILayer.h"


bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	

	auto menuItem1 = MenuItemImage::create(	"Images/Exit.png","Images/Exit_selected.png",
		CC_CALLBACK_1(UILayer::ClickExit, this));
	menuItem1->setScale(0.3f, 0.3f);

	auto winSize = Director::getInstance()->getWinSize();
	auto menu = Menu::create(menuItem1, NULL);
	menu->setPosition(winSize.width -40 , 12);
	this->addChild(menu);

	return true;
}

void UILayer::ClickExit(Ref* sender)
{
	Director::getInstance()->popScene();
}
