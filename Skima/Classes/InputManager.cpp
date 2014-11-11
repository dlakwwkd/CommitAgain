#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
	m_MouseLocation = Point::ZERO;
	m_MouseScrollStatus[SCROLL_LEFT] = false;
	m_MouseScrollStatus[SCROLL_RIGHT] = false;
	m_MouseScrollStatus[SCROLL_UP] = false;
	m_MouseScrollStatus[SCROLL_DOWN] = false;
	m_MouseScrollStatus[SCROLL_UPRIGHT] = false;
	m_MouseScrollStatus[SCROLL_DOWNRIGHT] = false;
	m_MouseScrollStatus[SCROLL_DOWNLEFT] = false;
	m_MouseScrollStatus[SCROLL_UPLEFT] = false;

}

void InputManager::CheckMouseScroll()
{
 	auto winSize = Director::getInstance()->getWinSize();

	if (m_MouseLocation.x < 20 && m_MouseLocation.y>20 && m_MouseLocation.y < winSize.height - 20){
		m_MouseScrollStatus[SCROLL_LEFT] = true;
 	}
	if (m_MouseLocation.x > 20 && m_MouseLocation.y>20 && m_MouseLocation.y < winSize.height - 20){
		m_MouseScrollStatus[SCROLL_LEFT] = false;
	}
	if (m_MouseLocation.x > winSize.width - 20 && m_MouseLocation.y>20 && m_MouseLocation.y < winSize.height - 20){
		m_MouseScrollStatus[SCROLL_RIGHT] = true;
	}
	if (m_MouseLocation.x < winSize.width - 20 && m_MouseLocation.y>20 && m_MouseLocation.y < winSize.height - 20){
		m_MouseScrollStatus[SCROLL_RIGHT] = false;
	}
	if (m_MouseLocation.y < 20 && m_MouseLocation.x > 20 && m_MouseLocation.x < winSize.width - 20){
		m_MouseScrollStatus[SCROLL_UP] = true;
	}
	if (m_MouseLocation.y > 20 && m_MouseLocation.x > 20 && m_MouseLocation.x < winSize.width - 20){
		m_MouseScrollStatus[SCROLL_UP] = false;
	}
	if (m_MouseLocation.y > winSize.height - 20 && m_MouseLocation.x > 20 && m_MouseLocation.x < winSize.width - 20){
		m_MouseScrollStatus[SCROLL_DOWN] = true;
	}
	if (m_MouseLocation.y < winSize.height - 20 && m_MouseLocation.x > 20 && m_MouseLocation.x < winSize.width - 20){
		m_MouseScrollStatus[SCROLL_DOWN] = false;
	}
	if (m_MouseLocation.x> winSize.width - 20 && m_MouseLocation.y < 20){
		m_MouseScrollStatus[SCROLL_UPRIGHT] = true;
		m_MouseScrollStatus[SCROLL_UP] = false;
		m_MouseScrollStatus[SCROLL_RIGHT] = false;
	}
	if (m_MouseLocation.x< winSize.width - 20 || m_MouseLocation.y > 20){
		m_MouseScrollStatus[SCROLL_UPRIGHT] = false;
	}
	if (m_MouseLocation.y < 20 && m_MouseLocation.x < 20){
		m_MouseScrollStatus[SCROLL_UPLEFT] = true;
		m_MouseScrollStatus[SCROLL_UP] = false;
		m_MouseScrollStatus[SCROLL_LEFT] = false;
	}
	if (m_MouseLocation.y > 20 || m_MouseLocation.x > 20){
		m_MouseScrollStatus[SCROLL_UPLEFT] = false;
	}
	if (m_MouseLocation.y > winSize.height - 20 && m_MouseLocation.x < 20){
		m_MouseScrollStatus[SCROLL_DOWNLEFT] = true;
		m_MouseScrollStatus[SCROLL_DOWN] = false;
		m_MouseScrollStatus[SCROLL_LEFT] = false;
	}
	if (m_MouseLocation.y < winSize.height - 20 || m_MouseLocation.x > 20){
		m_MouseScrollStatus[SCROLL_DOWNLEFT] = false;
	}
	if (m_MouseLocation.x > winSize.width - 20 && m_MouseLocation.y > winSize.height - 20){
		m_MouseScrollStatus[SCROLL_DOWNRIGHT] = true;
		m_MouseScrollStatus[SCROLL_DOWN] = false;
		m_MouseScrollStatus[SCROLL_RIGHT] = false;
	}
	if (m_MouseLocation.x < winSize.width - 20 || m_MouseLocation.y < winSize.height - 20){
		m_MouseScrollStatus[SCROLL_DOWNRIGHT] = false;
	}
}
