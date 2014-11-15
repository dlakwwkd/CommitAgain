#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
	Magician();
	Magician(int playerId, HeroType heroType, b2Vec2 pos);

	~Magician();
};

