#pragma once
#include "MapObject.h"
#include "GameManager.h"
class Lava_Damage;

class Lava : public MapObject
{
public:
    Lava(Player* owner, b2Vec2 createPos);
    virtual ~Lava();

    Rect* GetRange(){ return &m_Range; }

private:
    Rect            m_Range;
    Lava_Damage*    m_Damage;
};

