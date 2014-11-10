#pragma once
#include <map>

class Player;

typedef std::map<int, Player*> PlayerList;

class Game
{
public:
	Game(int id) : m_GameID(id), m_IsStart(false), m_LoadedPlayerNum(0) 
		, m_IsReady(true){}
	
	~Game(){}

	int					GetGameID(){ return m_GameID; }
	const PlayerList&	GetPlayerList(){ return m_PlayerList; }
	void				SetPlayerList(const std::vector<int>& playerIdList);
	
	void				SetIsStart(bool isStart){ m_IsStart = isStart; }
	bool				IsStart(){ return m_IsStart; }
	void				SetIsReady(bool isReady){ m_IsReady = isReady; }
	bool				IsReady(){ return m_IsReady; }

	void				InitGame();
	void				PlayerOut(int playerId);
	
	void				SetLoadedPlayerNum(){ m_LoadedPlayerNum++; }
	int					GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }
	Player*				GetPlayer(int playerId);

private:
	PlayerList			m_PlayerList;
	int					m_GameID;
	bool				m_IsReady;
	bool				m_IsStart;
	int					m_LoadedPlayerNum;

	
};

