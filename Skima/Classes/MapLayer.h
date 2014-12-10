#pragma once

USING_NS_CC;

#define MAX_MAP_SIZE_X 1680
#define MAX_MAP_SIZE_Y 1050

class MapLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MapLayer);

    void MakeObject(int id, Vec2 pos);
};

