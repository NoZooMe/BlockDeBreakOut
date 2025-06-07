#pragma once
#include "IBulletBehavior.h"
class StraightBehavior :
    public IBulletBehavior
{
public:
    void Update(Bullet& bullet) override;
};

