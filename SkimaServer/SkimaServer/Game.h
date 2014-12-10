﻿#pragma once
class Player;
class MapObject;
class GameRoom;

typedef std::map<int, Player*> PlayerList;
typedef std::vector<MapObject*> MapObjectList;

class Game
{
public:
    Game(GameRoom* room);
    ~Game();

    int                 GetGameID(){ return m_GameID; }
    const PlayerList&   GetPlayerList(){ return m_PlayerList; }
    int                 GetPlayerListSize(){ return m_PlayerList.size(); }
    
    void                SetIsStart(bool isStart){ m_IsStart = isStart; }
    void                SetIsReady(bool isReady){ m_IsReady = isReady; }
	void				SetIsEnd(bool isEnd){ m_IsEnd = isEnd; }
    bool                IsStart(){ return m_IsStart; }
    bool                IsReady(){ return m_IsReady; }
	bool				IsEnd(){ return m_IsEnd; }

    void                SetLoadedPlayerNum(){ m_LoadedPlayerNum++; }
    int                 GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }

    void                InitGame();
    void                InitMap();
	void				EndGame();
    Player*             GetPlayer(int playerId);
    void                OutPlayer(int playerId);

private:
    Player*             m_Computer;
    PlayerList          m_PlayerList;
    MapObjectList       m_MapObjectList;
    int                 m_GameID;
    bool                m_IsReady;
    bool                m_IsStart;
	bool				m_IsEnd;
    int                 m_LoadedPlayerNum;

};

