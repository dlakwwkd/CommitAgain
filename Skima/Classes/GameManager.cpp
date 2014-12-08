#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
    std::shared_ptr<InputManager> temp1(new InputManager());
    m_IM = temp1;
}
