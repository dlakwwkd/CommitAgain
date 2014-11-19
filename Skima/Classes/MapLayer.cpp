﻿#include "pch.h"
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
	sprite->setPosition(layerCenter);
	this->addChild(sprite);
// 
// 	this->addChild(particle);
// 	auto action = MoveTo::create(1, { 500, 500 });
// 	particle->runAction(action);
//	auto body = PhysicsBody::createEdgeBox(sprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
//	sprite->setPhysicsBody(body);
	return true;
}
