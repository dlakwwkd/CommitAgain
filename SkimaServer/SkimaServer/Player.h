#pragma once
#include "Hero.h"
#include "ObjectPool.h"
class ClientSession;

typedef std::map<int, Unit*> UnitList;

enum PlayerType
{
    PT_COMPUTER,
    PT_HUMAN,
};
enum Team
{
    TEAM_N,
    TEAM_A,
    TEAM_B,
    TEAM_C
};

class Player : public ObjectPool<Player>
{
public:
    Player(ClientSession* client, int playerId, const std::string& playerName, PlayerType type) :
        m_Client(client), m_PlayerID(playerId), m_PlayerName(playerName), m_PlayerType(type){}
    ~Player();

    ClientSession*      GetClient() const{ return m_Client; }
    const std::string&  GetPlayerName() const { return m_PlayerName; }
    int                 GetPlayerID() const { return m_PlayerID; }
    int                 GetRoomID() const { return m_RoomID; }
    Hero*               GetMyHero(){ return m_Hero; }
    Team                GetTeam(){ return m_Team; }
    const UnitList&     GetUnitList(){ return m_UnitList; }

    void                SetReady(bool ready) { m_IsReady = ready; }
    bool                IsReady() { return m_IsReady; }

    void			    CreateHero(const b2Vec2& pos);
    void                SetRoomID(int roomId){ m_RoomID = roomId; }
    void                SetHeroType(HeroType heroType){ m_HeroType = heroType; }
    void                SetTeam(Team team){ m_Team = team; }

    void                UnitListPush(int unitID, Unit* unit) { m_UnitList[unitID] = unit; }
    void                UnitListPop(int unitID);
    void                UnitListClear();

private:
    ClientSession*      m_Client    = nullptr;
    int                 m_PlayerID  = -1;
    std::string         m_PlayerName;
    PlayerType          m_PlayerType;

    Hero*               m_Hero      = nullptr;
    HeroType            m_HeroType  = HERO_NONE;
    Team                m_Team      = TEAM_N;
    int                 m_RoomID    = -1;
    bool                m_IsReady   = false;
    UnitList            m_UnitList;
};

