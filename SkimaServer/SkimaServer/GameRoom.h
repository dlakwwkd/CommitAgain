#pragma once
#include "ObjectPool.h"
#include "RefCountable.h"

class GameRoom : public RefCountable, public ObjectPool<GameRoom>
{
public:
	GameRoom(){}
	virtual ~GameRoom(){}



private:

};

