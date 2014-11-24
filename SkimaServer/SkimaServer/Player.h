#pragma once
#include "Hero.h"

typedef std::map<int, Unit*> UnitList;

class Player
{
public:
	Player(int playerId) : m_PlayerID(playerId), m_RoomID(-1), m_IsReady(false), m_Hero(nullptr), m_HeroType(HERO_NONE)
	{
		ZeroMemory(m_PlayerName, sizeof(m_PlayerName));
		itoa(playerId, m_PlayerName, 10);	// 임시로..
	}
	~Player();

	const char*	GetPlayerName() const { return m_PlayerName; }
	int			GetPlayerID() const { return m_PlayerID; }
	int			GetRoomID() const { return m_RoomID; }
	Hero*		GetMyHero(){ return m_Hero; }
	UnitList&	GetUnitList(){ return m_UnitList; }	//

	void		SetReady(bool ready) { m_IsReady = ready; }
	bool		IsReady() { return m_IsReady; }

	void		CreateHero(b2Vec2 pos);
	void		SetRoomID(int roomId){ m_RoomID = roomId; }
	void		SetHeroType(HeroType herotype) { m_HeroType = herotype; }
	void		UnitListPush(int unitID, Unit* unit) { m_UnitList[unitID] = unit; }
	void		UnitListPop(int unitID);

private:
	char		m_PlayerName[MAX_NAME_LEN];
	int			m_PlayerID;
	int			m_RoomID;
	bool		m_IsReady;

	Hero*		m_Hero;
	HeroType	m_HeroType;
	UnitList	m_UnitList;
};

