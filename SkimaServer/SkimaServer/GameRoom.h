#pragma once
#include "../../PacketType.h"
class Player;

typedef std::map<int, Player*> PlayerList;

class GameRoom
{
public:
    GameRoom(RoomInfo roomInfo, int roomNum) : m_ReadyNum(0), m_JoinAble(true), m_IsAllReady(false), m_IsGameExist(false)
    {
        m_RoomInfo = roomInfo;
        m_RoomInfo.mRoomNum = roomNum;
    }
    ~GameRoom(){}

    RoomInfo            GetRoomInfo(){ return m_RoomInfo; }
    int			        GetRoomID(){ return m_RoomInfo.mRoomNum; }
    int			        GetPlayerListSize(){ return m_PlayerList.size(); }
    void		        SetIsGameExist(bool isGameExist){ m_IsGameExist = isGameExist; }
    bool		        IsGameExist(){ return m_IsGameExist; }
    bool		        IsAllReady(){ return m_IsAllReady; }
    bool		        IsJoinAble(){ return m_JoinAble; }

    void		        ReadySign();
    void		        InitReady();
    const PlayerList&   GetPlayerList(){ return m_PlayerList; }
    void		        JoinPlayer(Player* player);
    void		        OutPlayer(int playerId);

private:
    PlayerList	m_PlayerList;
    RoomInfo    m_RoomInfo;
    int			m_ReadyNum;
    bool		m_JoinAble;
    bool		m_IsAllReady;
    bool		m_IsGameExist;

    friend class Game;
};

