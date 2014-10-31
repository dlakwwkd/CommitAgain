#pragma once
#include <map>

class Game;

class GameManager
{
public:
	GameManager(){}


private:
	typedef std::map<int, Game*> GameList;
	GameList	m_GameList;

};

extern GameManager* GGameManager;