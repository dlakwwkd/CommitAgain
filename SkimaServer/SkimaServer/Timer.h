#pragma once
#include "RefCountable.h"
#include "ObjectPool.h"
#include "Scheduler.h"
class Game;

enum TimerType
{
    TIMER_CALLBACK,
    TIMER_INFINITE,
    TIMER_REPEAT,
};

class Timer : public RefCountable, public ObjectPool<Timer>
{
public:
    Timer(int gameId);
    template <class... Args>
    Timer(Game* game, TimerType type, int delay, int repeatNum, Args&&... args);
    virtual ~Timer();

    void    SetOff(){ m_IsOn = false; }
    int     GetTimerId(){ return m_TimerID; }
    int     GetGameId(){ return m_GameID; }

    void    RepeatTimer(int repeatDelay, int repeatNum, const Task& func);
    void    WaitRepeatTimer(int repeatDelay, int repeatNum, const Task& func);
    void    InfiniteTimer(int repeatDelay, const Task& func);
    void    CallFuncOnce(int delay, const Task& func);
    
private:
    void    RunFunction(const Task& func);

private:
    bool    m_IsOn = true;
    int     m_TimerID = -1;
    int     m_GameID = -1;
};

