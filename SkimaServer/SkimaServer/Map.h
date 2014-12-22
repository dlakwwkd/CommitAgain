﻿#pragma once
#include "RefCountable.h"

#define MAX_MAP_SIZE_X 1680
#define MAX_MAP_SIZE_Y 1050

class MapObject;
class Player;
class Lava;

class Map
{
public:
    Map(int roomId);
    virtual ~Map();

    void InitMap(int roomId, Player* player);
    void LavaCreate(int roomId, Player* owner);

private:
    b2Body*    m_Body = nullptr;
};

