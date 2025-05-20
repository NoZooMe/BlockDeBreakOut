#pragma once
#include "IBulletBehavior.h"
class SpiralBehavior :
    public IBulletBehavior
{
    void Update(Bullet& bullet) override;
};

