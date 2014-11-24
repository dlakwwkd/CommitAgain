﻿#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
	Magician(int playerId, b2Vec2 pos);
	virtual ~Magician();
	
	virtual void UseSkill(SkillKey skillKey, b2Vec2 heroPos, b2Vec2 targetPos);
};

