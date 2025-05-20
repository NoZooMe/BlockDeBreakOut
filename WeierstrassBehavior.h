#pragma once
#include "IBulletBehavior.h"
class WeierstrassBehavior :
    public IBulletBehavior
{
    void Update(Bullet& bullet) override;
};

