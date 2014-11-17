#pragma once
#include <map>

class Player;

typedef std::map<int, Player*> PlayerList;

class Game
{
public:
	Game(int id) : m_GameID(id), m_IsStart(false), m_LoadedPlayerNum(0), m_IsReady(true){}
	~Game(){}

	int					GetGameID(){ return m_GameID; }
	const PlayerList&	GetPlayerList(){ return m_PlayerList; }
	void				SetPlayerList(PlayerList playerlist);
	
	void				SetIsStart(bool isStart){ m_IsStart = isStart; }
	void				SetIsReady(bool isReady){ m_IsReady = isReady; }
	bool				IsStart(){ return m_IsStart; }
	bool				IsReady(){ return m_IsReady; }

	void				SetLoadedPlayerNum(){ m_LoadedPlayerNum++; }
	int					GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }

	void				InitGame();
	void				PlayerOut(int playerId);
	Player*				GetPlayer(int playerId);

private:
	PlayerList			m_PlayerList;
	int					m_GameID;
	bool				m_IsReady;
	bool				m_IsStart;
	int					m_LoadedPlayerNum;
};

