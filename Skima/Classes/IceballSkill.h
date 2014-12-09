#pragma once
#include "ShootType.h"
class IceballSkill : public ShootType
{
public:
    IceballSkill();
    IceballSkill(Hero* hero);
    virtual ~IceballSkill();
};

