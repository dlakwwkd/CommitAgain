#include "pch.h"
#include "UILayer.h"


bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/*  �޴� play��ư
	auto menuItem1 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(UILayer::doClick1, this));
	auto menu = Menu::create(menuItem1, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);
	*/


	return true;
}

void UILayer::doClick1(Ref* sender)
{
	Director::getInstance()->popScene();
}
// 
// void UILayer::loadingMessage()
// {
// 	//�����ʿ�
// 
// 	if (this->getChildByName("ConnectLabel") != nullptr)
// 	{
// 		this->removeChildByName("ConnectLabel");
// 	}
// 		auto label = Label::createWithSystemFont("�ε� ��...", "Thonburi", 50);
// 	label->setAnchorPoint(Point(0.5,0.5));
// 	label->setHorizontalAlignment(TextHAlignment::CENTER);
// 	this->addChild(label, 0, "ConnectLabel");
// 
// 	//�Լ��� �Ÿݰ�
// 
// 
// }
