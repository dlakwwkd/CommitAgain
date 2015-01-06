#include "stdafx.h"
#include "Timer.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Game.h"


Timer::Timer(int gameId)
{
    m_TimerID = MakeID(this);
    m_GameID = gameId;
}
// 
// template <class... Args>
// Timer::Timer(Game* game, TimerType type, int delay, int repeatNum, Args&&... args)
// {
//     m_TimerID = MakeID(this);
//     m_GameID = game->GetGameID();
//     auto func = std::bind(std::forward<Args>(args)...);
//     switch (type)
//     {
//     case TIMER_CALLBACK:    CallFuncOnce(delay, func);              break;
//     case TIMER_INFINITE:    InfiniteTimer(delay, func);             break;
//     case TIMER_REPEAT:      RepeatTimer(delay, repeatNum, func);    break;
//     case TIMER_WAIT_REPEAT: WaitRepeatTimer(delay, repeatNum, func);break;
//     default:
//         break;
//     }
//     game->PushTimer(this);
// }


Timer::~Timer()
{
}

void Timer::RepeatTimer(int repeatDelay, int repeatNum, const Task& func)
{
    if (m_IsOn)
    {
        func();
        if (--repeatNum > 0)
        {
            CallFuncAfter(repeatDelay, this, &Timer::RepeatTimer, repeatDelay, repeatNum, func);
            return;
        }
    }
    CallFuncAfter(1, GGameManager, &GameManager::DestroyTimer, this);
}

void Timer::InfiniteTimer(int repeatDelay, const Task& func)
{
    if (m_IsOn)
    {
        func();
        CallFuncAfter(repeatDelay, this, &Timer::InfiniteTimer, repeatDelay, func);
        return;
    }
    CallFuncAfter(1, GGameManager, &GameManager::DestroyTimer, this);
}

void Timer::CallFuncOnce(int delay, const Task& func)
{
    CallFuncAfter(delay, this, &Timer::RunFunction, func);
}


void Timer::RunFunction(const Task& func)
{
    if (m_IsOn)
    {
        func();
        return;
    }
    CallFuncAfter(1, GGameManager, &GameManager::DestroyTimer, this);
}

void Timer::WaitRepeatTimer(int repeatDelay, int repeatNum, const Task& func)
{
    if (m_IsOn)
    {
        if (repeatNum > 0)
        {
            CallFuncAfter(repeatDelay, this, &Timer::RepeatTimer, repeatDelay, repeatNum, func);
            --repeatNum;
            return;
        }
    }
    CallFuncAfter(1, GGameManager, &GameManager::DestroyTimer, this);
}
