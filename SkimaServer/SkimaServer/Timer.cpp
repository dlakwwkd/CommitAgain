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
