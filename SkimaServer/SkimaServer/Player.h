#pragma once
#include "Hero.h"
#include "ObjectPool.h"
class ClientSession;
class Game;

typedef std::map<int, Unit*> UnitList;

enum PlayerType
{
    PT_COMPUTER,
    PT_HUMAN,
};

class Player : public ObjectPool<Player>
{
public:
    Player(ClientSession* client, const std::string& playerName, PlayerType type);
    virtual ~Player();

    ClientSession*      GetClient() const{ return m_Client; }
    std::string			GetPlayerName() const { return m_PlayerName; }
    int                 GetPlayerID() const { return m_PlayerID; }
    int                 GetRoomID() const { return m_RoomID; }
    Hero*               GetMyHero(){ return m_Hero; }
    Team                GetTeam(){ return m_Team; }
    const UnitList&     GetUnitList(){ return m_UnitList; }

    void                SetReady(bool ready) { m_IsReady = ready; }
    bool                IsReady() { return m_IsReady; }

    void                SetGame(Game* game){ m_Game = game; }
    Game*               GetGame(){ return m_Game; }

    void                InitGameOverStatus() { m_IsGameOver = false; }
    void                SetGameOver() { m_IsGameOver = true; }
    bool                IsGameOver() { return m_IsGameOver; }

    void			    CreateHero(const b2Vec2& pos, RoomType roomType);
    void                DeadHero();

    void                SetRoomID(int roomId){ m_RoomID = roomId; }
    void                SetHeroType(HeroType heroType){ m_HeroType = heroType; }
    void                SetTeam(Team team){ m_Team = team; }

    void                UnitListPush(int unitID, Unit* unit) { m_UnitList[unitID] = unit; }
    void                UnitListPop(int unitID);
    void                UnitListClear();

private:
    ClientSession*      m_Client        = nullptr;
    int                 m_PlayerID      = -1;
    std::string         m_PlayerName;
    PlayerType          m_PlayerType;

    Game*               m_Game          = nullptr;
    Hero*               m_Hero          = nullptr;
    HeroType            m_HeroType      = HERO_NONE;
    Team                m_Team          = TEAM_N;
    int                 m_RoomID        = -1;
    bool                m_IsReady       = false;
    bool                m_IsGameOver    = false;
    UnitList            m_UnitList;
};

