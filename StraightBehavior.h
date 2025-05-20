#pragma once
#include "IBulletBehavior.h"
#include <cmath>
class StraightBehavior :
    public IBulletBehavior
{
public:
    void Update(Bullet& bullet) override;
};

