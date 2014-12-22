#pragma once

USING_NS_CC;

struct RoomInfo;
class NetworkScene : public LayerColor
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(NetworkScene);

    void menuCallback1(Ref* sender);
    void menuCallback2(int roomNum);
    void menuCallback3(Ref* sender);

    void Tick(float dt);

    void ConnectLabelCreate(const char* str, NetworkScene* scene);
    void ConnectLabelChange(const char* str);
    void RoomInformation(RoomInfo roomInfo);
    void UpdateRoomInfo();
    void MakeRoomComplete(int roomId);
    void JoinRoomComplete(int roomId);

private:
    std::vector<RoomInfo>  m_RoomList;
};

