#pragma once
#include <map>

class Player;

typedef std::map<int, Player*> PlayerList;

class Game
{
public:
	Game(int id);
	~Game(){}

	int			GetGameID(){ return m_GameID; }
	PlayerList	GetPlayerList(){ return m_PlayerList; }
	void		SetPlayerList(std::vector<int> playerList);
	
	void	InitGame();

private:
	PlayerList			m_PlayerList;
	int					m_GameID;

	
};

