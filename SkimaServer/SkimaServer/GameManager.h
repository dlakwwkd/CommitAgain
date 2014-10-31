#pragma once
#include <map>

class Game;

class GameManager
{
public:
	GameManager(){}


private:
	typedef std::map<SOCKET, Game*> GameList;
	GameList	m_GameList;

};

extern GameManager* GClientManager;