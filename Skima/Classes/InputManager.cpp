#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
    m_MouseLocation = Vec2::ZERO;
}

void InputManager::InitTargetingKey()
{
    for (auto& key : m_Targeting)
    {
        key.second = false;
    }
}

EventKeyboard::KeyCode InputManager::SearchTargetingKey()
{
    for (auto& key : m_Targeting)
    {
        if (key.second == true)
        {
            return key.first;
        }
    }
    return EventKeyboard::KeyCode(-1);
}
