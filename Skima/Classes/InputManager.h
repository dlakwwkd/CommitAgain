#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define KEY_ENTER			EventKeyboard::KeyCode::KEY_ENTER
#define KEY_SPACE			EventKeyboard::KeyCode::KEY_SPACE
#define KEY_UP_ARROW		EventKeyboard::KeyCode::KEY_UP_ARROW
#define KEY_DOWN_ARROW		EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define KEY_LEFT_ARROW		EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define KEY_RIGHT_ARROW		EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define KEY_Z				EventKeyboard::KeyCode::KEY_Z
#define KEY_X				EventKeyboard::KeyCode::KEY_X

enum ScrollDir
{
	SCROLL_UP,
	SCROLL_DOWN,
	SCROLL_LEFT,
	SCROLL_RIGHT,
};

class InputManager
{
public:
	InputManager();

	Point	GetMouseLocation()										{ return m_MouseLocation; }
	bool	GetMouseStatus(int button)								{ return m_MouseStatus[button]; }
	bool    GetMouseScrollStatus(ScrollDir dir)						{ return m_MouseScrollStatus[dir]; }
	bool	GetKeyStatus(EventKeyboard::KeyCode key)				{ return m_KeyStatus[key]; }

	void	SetMouseLocation(Point p)								{ m_MouseLocation = p; }
	void	SetMouseStatus(int button, bool status)					{ m_MouseStatus[button] = status; }
	void	SetMouseScrollStatus(ScrollDir dir, bool status)		{ m_MouseScrollStatus[dir] = status; }
	void	SetKeyStatus(EventKeyboard::KeyCode key, bool status)	{ m_KeyStatus[key] = status; }

private:
	Point									m_MouseLocation;
	std::map<int, bool>						m_MouseStatus;
	std::map<ScrollDir, bool>				m_MouseScrollStatus;
	std::map<EventKeyboard::KeyCode, bool>	m_KeyStatus;
};