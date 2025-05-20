#pragma once
#include "IBulletBehavior.h"
class GravityBehavior :
    public IBulletBehavior
{
    void Update(Bullet& bullet) override;
};

