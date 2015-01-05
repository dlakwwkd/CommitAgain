#pragma once
#include "../../PacketType.h"
class Player;

typedef std::map<int, Player*> PlayerList;

class GameRoom
{
public:
    GameRoom(const RoomInfo& roomInfo) : m_ReadyNum(0), m_JoinAble(true), m_IsGameExist(false)
    {
        m_RoomInfo = roomInfo;
        m_RoomInfo.mRoomNum = MakeID(this);
    }
    ~GameRoom(){}

    const RoomInfo&     GetRoomInfo(){ return m_RoomInfo; }
    int			        GetRoomID(){ return m_RoomInfo.mRoomNum; }
    int			        GetPlayerListSize(){ return m_PlayerList.size(); }
    void		        SetIsGameExist(bool isGameExist){ m_IsGameExist = isGameExist; }
    bool		        IsGameExist(){ return m_IsGameExist; }
    void                SetIsGameStart(bool isStart){ m_RoomInfo.mIsAllReady = isStart; }
    bool		        IsAllReady(){ return m_RoomInfo.mIsAllReady; }
    bool		        IsJoinAble(){ return m_JoinAble; }

    void		        ReadySign();
    void		        InitReady();
    const PlayerList&   GetPlayerList(){ return m_PlayerList; }
    bool                JoinPlayer(Player* player);
    bool                OutPlayer(int playerId);

private:
    PlayerList	m_PlayerList;
    RoomInfo    m_RoomInfo;
    int			m_ReadyNum;
    bool		m_JoinAble;
    bool		m_IsGameExist;

    friend class Game;
};

