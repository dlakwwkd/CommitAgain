#pragma once
#include "Hero.h"
class ClientSession;

typedef std::map<int, Unit*> UnitList;

enum PlayerType
{
    COMPUTER,
    HUMAN,
};
enum Team
{
    NEUTRALITY,
    TEAM_A,
    TEAM_B,
};

class Player
{
public:
    Player(ClientSession* client, int playerId, PlayerType type) : 
        m_Client(client), m_PlayerType(type), m_Team(NEUTRALITY),
        m_PlayerID(playerId), m_RoomID(-1), m_IsReady(false), m_Hero(nullptr), m_HeroType(HERO_NONE)
    {
        ZeroMemory(m_PlayerName, sizeof(m_PlayerName));
        itoa(playerId, m_PlayerName, 10);	// 임시로..
    }
    ~Player();

    ClientSession*  GetClient() const{ return m_Client; }
    const char*	    GetPlayerName() const { return m_PlayerName; }
    int             GetPlayerID() const { return m_PlayerID; }
    int             GetRoomID() const { return m_RoomID; }
    Hero*           GetMyHero(){ return m_Hero; }
    Team            GetTeam(){ return m_Team; }
    const UnitList& GetUnitList(){ return m_UnitList; }

    void            SetReady(bool ready) { m_IsReady = ready; }
    bool            IsReady() { return m_IsReady; }

    void			CreateHero(const b2Vec2& pos);
    void            SetRoomID(int roomId){ m_RoomID = roomId; }
    void            SetHeroType(HeroType heroType){ m_HeroType = heroType; }
    void            SetTeam(Team team){ m_Team = team; }

    void            UnitListPush(int unitID, Unit* unit) { m_UnitList[unitID] = unit; }
    void            UnitListPop(int unitID);
    void            UnitListClear();

private:
    ClientSession*  m_Client;
    PlayerType      m_PlayerType;
    Team            m_Team;
    char            m_PlayerName[MAX_NAME_LEN];
    int             m_PlayerID;
    int             m_RoomID;
    bool            m_IsReady;

    Hero*           m_Hero;
    HeroType        m_HeroType;
    UnitList        m_UnitList;
};

