#pragma once
#include "RefCountable.h"
#include "ObjectPool.h"
#include "Scheduler.h"
#include "Game.h"
enum TimerType
{
    TIMER_INFINITE,
};

class Timer : public RefCountable, public ObjectPool<Timer>
{
public:
    static void Push(){}
    template <class T, typename F, typename... Args>
    // - InfiniteTimer
    static Timer* Push(Game* game, int repeatDelay, TimerType type, T instance, F memfunc, Args&&... args)
    {
        auto func = std::bind(memfunc, instance, std::forward<Args>(args)...);
        auto timer = new Timer(game->GetGameID());
        timer->InfiniteTimer(repeatDelay, func);
        game->PushTimer(timer);
        return timer;
    }
    template <class T, typename F, typename... Args>
    // - RepeatTimer
    static void Push(Game* game, int repeatDelay, int repeatNum, T instance, F memfunc, Args&&... args)
    {
        auto func = std::bind(memfunc, instance, std::forward<Args>(args)...);
        auto timer = new Timer(game->GetGameID());
        timer->RepeatTimer(repeatDelay, repeatNum, func);
        game->PushTimer(timer);
    }
    template <class T, typename F, typename... Args>
    // - WaitRepeatTimer 
    static void Push(Game* game, int delay, int repeatDelay, int repeatNum, T instance, F memfunc, Args&&... args)
    {
        auto func = std::bind(memfunc, instance, std::forward<Args>(args)...);
        auto timer = new Timer(game->GetGameID());
        timer->WaitRepeatTimer(delay, repeatDelay, repeatNum, func);
        game->PushTimer(timer);
    }
    template <class T, typename F, typename... Args>
    // - CallFuncOnce
    static void Push(Game* game, int delay, T instance, F memfunc, Args&&... args)
    {
        auto func = std::bind(memfunc, instance, std::forward<Args>(args)...);
        auto timer = new Timer(game->GetGameID());
        timer->CallFuncOnce(delay, func);
        game->PushTimer(timer);
    }
    virtual ~Timer();

    void    SetOff(){ m_IsOn = false; }
    int     GetTimerId(){ return m_TimerID; }
    int     GetGameId(){ return m_GameID; }

private:
    Timer(int gameId)
    {
        m_TimerID = MakeID(this);
        m_GameID = gameId;
    }
    void    RepeatTimer(int repeatDelay, int repeatNum, const Task& func);
    void    InfiniteTimer(int repeatDelay, const Task& func);
    void    WaitRepeatTimer(int delay, int repeatDelay, int repeatNum, const Task& func);
    void    CallFuncOnce(int delay, const Task& func);
    void    RunFunction(const Task& func);

private:
    bool    m_IsOn = true;
    int     m_TimerID = -1;
    int     m_GameID = -1;
};

