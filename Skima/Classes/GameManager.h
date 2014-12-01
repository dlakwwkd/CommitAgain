#pragma once
#include "Enums.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "EffectManager.h"

USING_NS_CC;

#define GET_GM GameManager::getInstance()
#define GET_IM GameManager::getInstance().getInputManager()
#define GET_MM GameManager::getInstance().getMissileManager()
#define GET_EM GameManager::getInstance().getEffectManger()

class GameManager
{
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	std::shared_ptr<InputManager>	getInputManager(){ return m_IM; }
	std::shared_ptr<ObjectManager>	getMissileManager(){ return m_OM; }
	std::shared_ptr<EffectManager>	getEffectManger(){ return m_EM; }

	void							SetGameMode(GameMode mode){ m_Mode = mode; }
	GameMode						GetGameMode(){ return m_Mode; }

private:
	GameManager();
	std::shared_ptr<InputManager>	m_IM;
	std::shared_ptr<ObjectManager>	m_OM;
	std::shared_ptr<EffectManager>	m_EM;

	GameMode						m_Mode;
};