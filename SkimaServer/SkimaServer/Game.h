#pragma once
class Player;
class GameRoom;

typedef std::map<int, Player*> PlayerList;

class Game
{
public:
    Game(GameRoom* room);
	~Game(){}

	int					GetGameID(){ return m_GameID; }
	const PlayerList&	GetPlayerList(){ return m_PlayerList; }
	
	void				SetIsStart(bool isStart){ m_IsStart = isStart; }
	void				SetIsReady(bool isReady){ m_IsReady = isReady; }
	bool				IsStart(){ return m_IsStart; }
	bool				IsReady(){ return m_IsReady; }

	void				SetLoadedPlayerNum(){ m_LoadedPlayerNum++; }
	int					GetLoadedPlayerNum(){ return m_LoadedPlayerNum; }

	void				InitGame();
	Player*				GetPlayer(int playerId);
    void			 	OutPlayer(int id);

private:
	PlayerList      	m_PlayerList;
	int					m_GameID;
	bool				m_IsReady;
	bool				m_IsStart;
	int					m_LoadedPlayerNum;

};

