#pragma once

#define MAX_MAP_SIZE_X 1680
#define MAX_MAP_SIZE_Y 1050

class MapObject;
class Player;

typedef std::vector<MapObject*> MapObjectList;

class Map
{
public:
    Map(int roomId);
    ~Map();

    void InitMap(int roomId, Player* player);
    void ObjectBreak();
    void ObjectListClear();

private:
    b2Body*         m_Body;
    MapObjectList   m_MapObjectList;
};

