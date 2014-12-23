#pragma once
#include "RefCountable.h"

#define MAX_MAP_SIZE_X  1680
#define MAX_MAP_SIZE_Y  1050
#define INIT_ROCK_NUM   10

class MapObject;
class Player;
class Lava;

class Map
{
public:
    Map(int roomId);
    virtual ~Map();

    void InitMap(Player* player, int roomId);
    void LavaCreate(Player* player, int roomId);

private:
    b2Body*    m_Body = nullptr;
};

