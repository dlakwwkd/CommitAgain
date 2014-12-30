#pragma once
#include "../../PacketType.h"
class Player;
class MapObject;
class GameRoom;
class Map;
class Unit;
class Timer;
class WaveSystem;

typedef std::map<int, Player*>  PlayerList;
typedef std::map<int, Timer*>   TimerList;

class Game
{
public:
    Game(GameRoom* room);
    ~Game();

    int                 GetGameID(){ return m_GameID; }
    int                 GetPlayerListSize(){ return m_PlayerList.size(); }
    bool                IsStart(){ return m_IsStart; }
    void                SetLoadedPlayerNum(){ ++m_LoadedPlayerNum; }
    int                 GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }
    Map*                GetMap(){ return m_Map; }

    void                Tick(float dt);
    void                PushTimer(Timer* timer);
    void                PopTimer(int timerId);

    void                InitGame(RoomType roomType);
    void                StartGame();
	void				EndGame();

    Player*             GetPlayer(int playerId);
    void                OutPlayer(int playerId);

    void                Targeting(Unit* caster);

private:
    PlayerList          m_PlayerList;
    TimerList           m_TimerList;
    WaveSystem*         m_WaveSystem = nullptr;
    Player*             m_Computer = nullptr;
    Map*                m_Map = nullptr;
    bool                m_IsStart;
    int                 m_GameID;
    int                 m_LoadedPlayerNum;

    friend class GameManager;
};

