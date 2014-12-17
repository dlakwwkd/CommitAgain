#pragma once
#include "InputManager.h"

USING_NS_CC;

#define GET_GM GameManager::getInstance()
#define GET_IM GameManager::getInstance().getInputManager()

class GameManager
{
public:
    static GameManager& getInstance()
    {
        static GameManager instance;
        return instance;
    }
	std::shared_ptr<InputManager>	getInputManager(){ return m_IM; }

private:
    GameManager();
	std::shared_ptr<InputManager>   m_IM = nullptr;
};