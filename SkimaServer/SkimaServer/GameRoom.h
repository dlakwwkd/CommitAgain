#pragma once
class Player;

typedef std::map<int, Player*> PlayerList;

class GameRoom
{
public:
    GameRoom(int id) : m_RoomID(id), m_ReadyNum(0), m_JoinAble(true), m_IsAllReady(false), m_IsGameExist(false){}
    ~GameRoom(){}

    int                 GetRoomID(){ return m_RoomID; }
    int                 GetPlayerListSize(){ return m_PlayerList.size(); }
    void                SetIsGameExist(bool isGameExist){ m_IsGameExist = isGameExist; }
    bool                IsGameExist(){ return m_IsGameExist; }
    bool                IsAllReady(){ return m_IsAllReady; }
    bool                IsJoinAble(){ return m_JoinAble; }

    void                ReadySign();
    void                InitReady();
    void                JoinPlayer(Player* player);
    void                OutPlayer(int playerId);

private:
    PlayerList          m_PlayerList;
    int                 m_RoomID;
    int                 m_ReadyNum;
    bool                m_JoinAble;
    bool                m_IsAllReady;
    bool                m_IsGameExist;

    friend class Game;
};

