#pragma once
#include <map>

class Player;

typedef std::map<int, Player*> PlayerList;

class Game
{
public:
	Game(int id);
	~Game(){}

	int					GetGameID(){ return m_GameID; }
	const PlayerList&	GetPlayerList(){ return m_PlayerList; }
	void				SetPlayerList(const std::vector<int>& playerIdList);
	
	void				InitGame();
	void				PlayerOut(int playerId);

private:
	PlayerList			m_PlayerList;
	int					m_GameID;

	
};

