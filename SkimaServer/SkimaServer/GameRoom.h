#pragma once
class Player;

typedef std::map<int, Player*> PlayerList;

class GameRoom
{
public:
    GameRoom(int id) : m_RoomID(id), m_JoinAble(true), m_ReadyNum(0), m_IsAllReady(false), m_IsGameExist(false){}
    ~GameRoom(){}

    int                 GetRoomID(){ return m_RoomID; }
    const PlayerList&   GetPlayerList(){ return m_PlayerList; }
    int                 GetPlayerNum(){ return m_ReadyNum; }

    void                SetIsGameExist(bool isGameExist){ m_IsGameExist = isGameExist; }

    bool                IsJoinAble(){ return m_JoinAble; }
    bool                IsAllReady(){ return m_IsAllReady; }
    bool                IsGameExist(){ return m_IsGameExist; }
    void                InitReady();

    void                ReadySign();
    void                JoinPlayer(Player* player);
    void                OutPlayer(int id);

private:
    PlayerList          m_PlayerList;
    int                 m_RoomID;
    int                 m_ReadyNum;
    bool                m_JoinAble;
    bool                m_IsAllReady;
    bool                m_IsGameExist;

    friend class Game;
};

