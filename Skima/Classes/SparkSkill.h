#pragma once
#include "ShootType.h"
class SparkSkill : public ShootType
{
public:
    SparkSkill();
    SparkSkill(Hero* hero);
    virtual ~SparkSkill();
};

