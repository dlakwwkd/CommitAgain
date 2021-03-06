﻿#pragma once
#include "InputManager.h"

USING_NS_CC;

#define GET_GM GameManager::getInstance()
#define GET_IM GameManager::getInstance().getInputManager()

class Player;

class GameManager
{
public:
    static GameManager& getInstance()
    {
        static GameManager instance;
        return instance;
    }
	std::shared_ptr<InputManager>	getInputManager(){ return m_IM; }

	Player* GetPlayer(int id);
	void	SetPlayer(int id);
	void	DeletePlayer(int id);
	void	DeletePlayerAll();

private:
    GameManager();
	std::shared_ptr<InputManager>   m_IM = nullptr;

	std::map<int, Player*>			m_PlayerList;
};