#pragma once
class Player;
class MapObject;
class GameRoom;
class Map;

typedef std::map<int, Player*> PlayerList;
typedef std::vector<MapObject*> MapObjectList;

class Game
{
public:
    Game(GameRoom* room);
    ~Game();

    int                 GetGameID(){ return m_GameID; }
    int                 GetPlayerListSize(){ return m_PlayerList.size(); }
    void                SetIsStart(bool isStart){ m_IsStart = isStart; }
    bool                IsStart(){ return m_IsStart; }
    void                SetLoadedPlayerNum(){ ++m_LoadedPlayerNum; }
    int                 GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }

    void                Tick(float dt);
    void                InitGame();
    void                InitMap();
	void				EndGame();
    Player*             GetPlayer(int playerId);
    void                OutPlayer(int playerId);

private:
    Player*             m_Computer;
    PlayerList          m_PlayerList;
    MapObjectList       m_MapObjectList;
    Map*                m_Map;
    int                 m_GameID;
    bool                m_IsStart;
    int                 m_LoadedPlayerNum;

    friend class GameManager;
};

