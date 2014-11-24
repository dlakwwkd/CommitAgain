#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
	std::shared_ptr<InputManager> temp1(new InputManager());
	std::shared_ptr<MissileManager> temp2(new MissileManager());
	m_IM = temp1;
	m_MM = temp2;
}
