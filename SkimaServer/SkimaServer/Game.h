#pragma once
#include "RefCountable.h"
#include "Scheduler.h"
class Player;
class MapObject;
class GameRoom;
class Map;
class Unit;

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
    Map*                GetMap(){ return m_Map; }

    void                Tick(float dt);
    void                RepeatTimer(int repeatDelay, int repeatNum, const Task& func);
    void                InfiniteTimer(int repeatDelay, const Task& func);

    void                InitGame();
    void                StartGame();
	void				EndGame();

    Player*             GetPlayer(int playerId);
    void                OutPlayer(int playerId);

    void                MobWaveSystem();
    void                Targeting(Unit* caster);

private:
    PlayerList          m_PlayerList;
    Player*             m_Computer = nullptr;
    Map*                m_Map = nullptr;
    bool                m_IsStart;
    int                 m_GameID;
    int                 m_LoadedPlayerNum;

    friend class GameManager;
};

