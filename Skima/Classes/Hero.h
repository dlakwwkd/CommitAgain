#pragma once
#include "Unit.h"
class Hero :
	public Unit
{
public:
	Hero();
	~Hero();

protected:
	HeroType m_HeroType;
};

