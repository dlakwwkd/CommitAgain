#pragma once
#include "ObjectPool.h"
#include "RefCountable.h"

class Game : public RefCountable, public ObjectPool<Game>
{
public:
	Game(){}
	virtual ~Game(){}
};

