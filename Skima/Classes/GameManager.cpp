#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
    std::shared_ptr<InputManager> temp1(new InputManager()); ///< 왜 이렇게?? make_shared
    m_IM = temp1;
}
