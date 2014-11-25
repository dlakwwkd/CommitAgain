#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
	m_MouseLocation = Point::ZERO;
	m_MouseScrollStatus[SCROLL_LEFT] = false;
	m_MouseScrollStatus[SCROLL_RIGHT] = false;
	m_MouseScrollStatus[SCROLL_UP] = false;
	m_MouseScrollStatus[SCROLL_DOWN] = false;
}

void InputManager::CheckMouseScroll()
{
 	auto winSize = Director::getInstance()->getWinSize();

	if (m_MouseLocation.x < 50)						m_MouseScrollStatus[SCROLL_LEFT] = true;
	if (m_MouseLocation.x > 50)						m_MouseScrollStatus[SCROLL_LEFT] = false;
	if (m_MouseLocation.x > winSize.width - 50)		m_MouseScrollStatus[SCROLL_RIGHT] = true;
	if (m_MouseLocation.x < winSize.width - 50)		m_MouseScrollStatus[SCROLL_RIGHT] = false;
	if (m_MouseLocation.y < 50)						m_MouseScrollStatus[SCROLL_UP] = true;
	if (m_MouseLocation.y > 50)						m_MouseScrollStatus[SCROLL_UP] = false;
	if (m_MouseLocation.y > winSize.height - 50)		m_MouseScrollStatus[SCROLL_DOWN] = true;
	if (m_MouseLocation.y < winSize.height - 50)		m_MouseScrollStatus[SCROLL_DOWN] = false;
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
