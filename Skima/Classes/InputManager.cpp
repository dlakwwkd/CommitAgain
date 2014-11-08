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

	if (m_MouseLocation.x < 5){
		m_MouseScrollStatus[SCROLL_LEFT] = true;
 	}
	if (m_MouseLocation.x > 5){
		m_MouseScrollStatus[SCROLL_LEFT] = false;
	}
	if (m_MouseLocation.x > winSize.width - 5){
		m_MouseScrollStatus[SCROLL_RIGHT] = true;
	}
	if (m_MouseLocation.x < winSize.width - 5){
		m_MouseScrollStatus[SCROLL_RIGHT] = false;
	}
	if (m_MouseLocation.y < 5){
		m_MouseScrollStatus[SCROLL_UP] = true;
	}
	if (m_MouseLocation.y > 5){
		m_MouseScrollStatus[SCROLL_UP] = false;
	}
	if (m_MouseLocation.y > winSize.height - 5){
		m_MouseScrollStatus[SCROLL_DOWN] = true;
	}
	if (m_MouseLocation.y < winSize.height - 5){
		m_MouseScrollStatus[SCROLL_DOWN] = false;
	}
}
