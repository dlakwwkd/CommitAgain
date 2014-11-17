#pragma once
#include "ListenerLayer.h"

USING_NS_CC;

#define KEY_ENTER			EventKeyboard::KeyCode::KEY_ENTER
#define KEY_SPACE			EventKeyboard::KeyCode::KEY_SPACE
#define KEY_UP_ARROW		EventKeyboard::KeyCode::KEY_UP_ARROW
#define KEY_DOWN_ARROW		EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define KEY_LEFT_ARROW		EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define KEY_RIGHT_ARROW		EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define KEY_Q				EventKeyboard::KeyCode::KEY_Q
#define KEY_W				EventKeyboard::KeyCode::KEY_W
#define KEY_E				EventKeyboard::KeyCode::KEY_E
#define KEY_R				EventKeyboard::KeyCode::KEY_R

enum ScrollDir
{
// 	SCROLL_HORI,
// 	SCROLL_VERTI,
	SCROLL_UP,
	SCROLL_DOWN,
	SCROLL_LEFT,
	SCROLL_RIGHT,
// 	SCROLL_UPRIGHT,
// 	SCROLL_DOWNRIGHT,
// 	SCROLL_UPLEFT,
// 	SCROLL_DOWNLEFT,
// 	
};

class InputManager
{
public:
	InputManager();

	Point	GetMouseLocation()										{ return m_MouseLocation; }
	bool	GetMouseStatus(int button)								{ return m_MouseStatus[button]; }
	bool    GetMouseScrollStatus(ScrollDir dir)						{ return m_MouseScrollStatus[dir]; }
	bool	GetKeyStatus(EventKeyboard::KeyCode key)				{ return m_KeyStatus[key]; }
	bool	GetTargeting(EventKeyboard::KeyCode key)				{ return m_Targeting[key]; }

	void	SetMouseLocation(Point p)								{ m_MouseLocation = p; }
	void	SetMouseStatus(int button, bool status)					{ m_MouseStatus[button] = status; }
	void	SetMouseScrollStatus(ScrollDir dir, bool status)		{ m_MouseScrollStatus[dir] = status; }
	void	SetKeyStatus(EventKeyboard::KeyCode key, bool status)	{ m_KeyStatus[key] = status; }
	void	SetTargeting(EventKeyboard::KeyCode key, bool status)	{ m_Targeting[key] = status; }

	void					CheckMouseScroll();
	EventKeyboard::KeyCode	SearchTargetingKey();

private:
	Point									m_MouseLocation;
	std::map<int, bool>						m_MouseStatus;
	std::map<ScrollDir,bool>				m_MouseScrollStatus;
	std::map<EventKeyboard::KeyCode, bool>	m_KeyStatus;
	std::map<EventKeyboard::KeyCode, bool>	m_Targeting;
};