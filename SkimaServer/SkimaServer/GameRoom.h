#pragma once
#include "../../PacketType.h"
class Player;

typedef std::map<int, Player*> PlayerList;

class GameRoom
{
public:
    GameRoom(const RoomInfo& roomInfo) : m_RoomInfo(roomInfo), m_JoinAble(true), m_IsGameExist(false), m_LoadedPlayerNum(0)
    {
        m_RoomInfo.mRoomNum = MakeID(this);
    }
    ~GameRoom(){}

    int			        GetRoomID(){ return m_RoomInfo.mRoomNum; }
    const RoomInfo&     GetRoomInfo(){ return m_RoomInfo; }
    int			        GetPlayerListSize(){ return m_PlayerList.size(); }
    void		        SetIsGameExist(bool isGameExist){ m_IsGameExist = isGameExist; }
    void                SetIsGameStart(bool isStart){ m_RoomInfo.mIsAllReady = isStart; }
    void                SetLoadedPlayerNum(){ ++m_LoadedPlayerNum; }
    int                 GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }
    bool		        IsGameExist(){ return m_IsGameExist; }
    bool		        IsAllReady(){ return m_RoomInfo.mIsAllReady; }
    bool		        IsJoinAble(){ return m_JoinAble; }

    void		        ReadySign();
    void		        InitReady();
    bool                JoinPlayer(Player* player);
    bool                OutPlayer(int playerId);

private:
    PlayerList	m_PlayerList;
    RoomInfo    m_RoomInfo;
    bool		m_JoinAble;
    bool		m_IsGameExist;
    int         m_LoadedPlayerNum;

    friend class Game;
};

