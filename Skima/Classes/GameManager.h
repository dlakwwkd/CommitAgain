#pragma once
#include "Enums.h"
#include "InputManager.h"
#include "MissileManager.h"

USING_NS_CC;

#define GET_GM GameManager::getInstance()
#define GET_IM GameManager::getInstance().getInputManager()
#define GET_MM GameManager::getInstance().getMissileManager()

class GameManager
{
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	std::shared_ptr<InputManager>	getInputManager(){ return m_IM; }
	std::shared_ptr<MissileManager>	getMissileManager(){ return m_MM; }

	void							SetGameMode(GameMode mode){ m_Mode = mode; }
	GameMode						GetGameMode(){ return m_Mode; }

private:
	GameManager();
	std::shared_ptr<InputManager>	m_IM;
	std::shared_ptr<MissileManager>	m_MM;

	GameMode						m_Mode;
};