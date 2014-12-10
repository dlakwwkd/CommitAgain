#pragma once

#define MAX_MAP_SIZE_X 1680
#define MAX_MAP_SIZE_Y 1050

class Map
{
public:
    Map(int roomId);
    ~Map();

private:
    b2Body* m_Body;
};

