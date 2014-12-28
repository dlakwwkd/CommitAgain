#pragma once
#include "PacketType.h"

USING_NS_CC;

class MakeRoomLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MakeRoomLayer);

    void    UpMaxPlayerNum();
    void    DownMaxPlayerNum();
    void    ChangeRoomMode(RoomType roomMode);
    void    MakeRoom();
    void    CancelMakeRoom();
private:
    RoomInfo    m_MakeRoomInfo;
};

