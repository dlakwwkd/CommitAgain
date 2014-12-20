#pragma once
#include "RefCountable.h"
class Player;
class MapObject;
class GameRoom;
class Map;

typedef std::map<int, Player*> PlayerList;

class Game : public RefCountable
{
public:
    Game(GameRoom* room);
    ~Game();

    int                 GetGameID(){ return m_GameID; }
    int                 GetPlayerListSize(){ return m_PlayerList.size(); }
    bool                IsStart(){ return m_IsStart; }
    void                SetLoadedPlayerNum(){ ++m_LoadedPlayerNum; }
    int                 GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }

    void                Tick(float dt);
    void                WaveTimer();
    void                InitGame();
    void                StartGame();
	void				EndGame();
    Player*             GetPlayer(int playerId);
    void                OutPlayer(int playerId);
    Map*                GetMap(){ return m_Map; }

private:
    PlayerList          m_PlayerList;
    Player*             m_Computer = nullptr;
    Map*                m_Map = nullptr;
    bool                m_IsStart;
    int                 m_GameID;
    int                 m_LoadedPlayerNum;

    friend class GameManager;
};

