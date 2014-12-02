#include "pch.h"
#include "GameManager.h"

GameManager::GameManager()
{
    std::shared_ptr<InputManager> temp1(new InputManager());
    std::shared_ptr<EffectManager> temp3(new EffectManager());
    m_IM = temp1;
    m_EM = temp3;
}
