#pragma once
#include "Effect.h"
class SparkEffect : public Effect
{
public:
    SparkEffect();
    virtual ~SparkEffect();

    virtual void CreateEffect(Vec2 createPos);
    virtual void ExtinctEffect();

};

