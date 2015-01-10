#pragma once
struct RoomInfo;

USING_NS_CC;

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

    void PushRoomInfo(const RoomInfo& roomInfo);
    void UpdateRoomInfo();
    void ClearRoomInfo();

    void MakeRoomComplete(const RoomInfo& roomInfo);
    void JoinRoomComplete(const RoomInfo& roomInfo);

private:
    std::vector<RoomInfo>  m_RoomList;
};

