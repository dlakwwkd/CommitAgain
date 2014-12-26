#pragma once
#include "ShootType.h"
class FireballSkill : public ShootType
{
public:
    FireballSkill(Hero* hero);
    virtual ~FireballSkill();
};

