#pragma once
#include <map>

class Player;

typedef std::map<int, Player*> PlayerList;

class Game
{
public:
	Game(int id) : m_GameID(id), m_IsStart(false), m_LoadedPlayerNum(0) {}
	~Game(){}

	int					GetGameID(){ return m_GameID; }
	const PlayerList&	GetPlayerList(){ return m_PlayerList; }
	void				SetPlayerList(const std::vector<int>& playerIdList);
	
	void				SetIsStart(){ m_IsStart = true; }
	bool				GetIsStart(){ return m_IsStart; }

	void				InitGame();
	void				PlayerOut(int playerId);
	
	void				SetLoadedPlayerNum(){ m_LoadedPlayerNum++; }
	int					GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }
	Player*				GetPlayer(int palyerId);

private:
	PlayerList			m_PlayerList;
	int					m_GameID;
	bool				m_IsStart;
	int					m_LoadedPlayerNum;

	
};

