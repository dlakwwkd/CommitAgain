#pragma once
class Game;

class WaveSystem
{
public:
    WaveSystem(Game* game);
    ~WaveSystem();

    void    WaveLoop();
    void    WaveProcess();

private:
    Game*   m_Game = nullptr;
    b2Vec2  m_RegenPos;
    int     m_WaveNum;
};

