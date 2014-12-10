#pragma once

USING_NS_CC;

class MapLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MapLayer);

    void MakeObject(int id, Vec2 pos);
};

