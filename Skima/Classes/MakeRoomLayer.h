#pragma once
#include "PacketType.h"

USING_NS_CC;

//struct RoomInfo;
class MakeRoomLayer : Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MakeRoomLayer);

    void    UpMaxPlayerNum();
    void    DownMaxPlayerNum();

private:
    RoomInfo    m_MakeRoomInfo;
};

