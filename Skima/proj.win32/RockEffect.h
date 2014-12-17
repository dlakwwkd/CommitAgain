#pragma once
#include "C:\cocos2d-x\projects\CommitAgain\Skima\Classes\Effect.h"
class RockEffect :
    public Effect
{
public:
    RockEffect();
    ~RockEffect();

    void CreateEffect(Vec2 createPos);
    void ExtinctEffect();
};

