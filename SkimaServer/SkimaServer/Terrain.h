#pragma once

class Player;

class Terrain
{
public:
    Terrain();
    ~Terrain();

protected:
    Player* m_Owner;
    b2Vec2 m_Pos;
    int m_Damage;
};

