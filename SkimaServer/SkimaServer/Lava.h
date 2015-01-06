#pragma once
#include "MapObject.h"
#include "GameManager.h"
class LavaDamageSkill;

class Lava : public MapObject
{
public:
    Lava(Player* owner, b2Vec2 createPos);
    virtual ~Lava();

    Rect* GetRange(){ return &m_Range; }

private:
    Rect            m_Range;
    LavaDamageSkill*    m_Damage;
};

