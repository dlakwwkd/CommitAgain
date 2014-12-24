#pragma once
#include "RefCountable.h"
#include "ObjectPool.h"
#include "Scheduler.h"

class Timer : public RefCountable, public ObjectPool<Timer>
{
public:
    Timer(int gameId);
    ~Timer();

    int     GetTimerId(){ return m_TimerID; }
    void    SetOff(){ m_IsOn = false; }

    void    RepeatTimer(int repeatDelay, int repeatNum, const Task& func);
    void    InfiniteTimer(int repeatDelay, const Task& func);
    void    CallFuncOnce(int delay, const Task& func);
    
private:
    void    RunFunction(const Task& func);

private:
    int     m_TimerID = -1;
    int     m_GameID = -1;
    bool    m_IsOn = true;
};

