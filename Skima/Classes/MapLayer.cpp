#include "MapLayer.h"


bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto layerCenter = this->getAnchorPointInPoints();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto sprite = Sprite::create("Images/bg1.png");
	auto body = PhysicsBody::createEdgeBox(sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	sprite->setPhysicsBody(body);
	sprite->setPosition(layerCenter);

	this->addChild(sprite);
	return true;
}
