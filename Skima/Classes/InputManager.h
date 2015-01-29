#pragma once
#include "ListenerLayer.h"

USING_NS_CC;

#define KEY_ENTER           EventKeyboard::KeyCode::KEY_ENTER
#define KEY_SPACE           EventKeyboard::KeyCode::KEY_SPACE
#define KEY_ESC             EventKeyboard::KeyCode::KEY_ESCAPE
#define KEY_UP_ARROW        EventKeyboard::KeyCode::KEY_UP_ARROW
#define KEY_DOWN_ARROW      EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define KEY_LEFT_ARROW      EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define KEY_RIGHT_ARROW     EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define KEY_Q               EventKeyboard::KeyCode::KEY_Q
#define KEY_W               EventKeyboard::KeyCode::KEY_W
#define KEY_E               EventKeyboard::KeyCode::KEY_E
#define KEY_R               EventKeyboard::KeyCode::KEY_R

class InputManager
{
public:
    InputManager();

    Vec2	GetMouseLocation()                                      { return m_MouseLocation; }
    bool	GetMouseStatus(int button)                              { return m_MouseStatus[button]; }
    bool	GetKeyStatus(EventKeyboard::KeyCode key)                { return m_KeyStatus[key]; }
    bool	GetTargeting(EventKeyboard::KeyCode key)                { return m_Targeting[key]; }

    void	SetMouseLocation(Vec2 p)                                { m_MouseLocation = p; }
    void	SetMouseStatus(int button, bool status)                 { m_MouseStatus[button] = status; }
    void	SetKeyStatus(EventKeyboard::KeyCode key, bool status)   { m_KeyStatus[key] = status; }
    void	SetTargeting(EventKeyboard::KeyCode key, bool status)   { m_Targeting[key] = status; }

    void                    InitTargetingKey();
    EventKeyboard::KeyCode  SearchTargetingKey();

private:
    Vec2                                    m_MouseLocation;
    std::map<int, bool>                     m_MouseStatus;
    std::map<EventKeyboard::KeyCode, bool>  m_KeyStatus;
    std::map<EventKeyboard::KeyCode, bool>  m_Targeting;
};