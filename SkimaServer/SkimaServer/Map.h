#pragma once
#include "RefCountable.h"

#define MAX_MAP_SIZE_X 1680
#define MAX_MAP_SIZE_Y 1050

class MapObject;
class Player;
class Lava;

typedef std::map<int, Lava*> LavaList;

class Map : public RefCountable
{
public:
    Map(int roomId);
    virtual ~Map();

    void InitMap(int roomId, Player* player);
    void LavaDamage();
    void ObjectListClear();

private:
    b2Body*    m_Body = nullptr;
    LavaList   m_LavaList;
};

