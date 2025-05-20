#pragma once
#include "IBulletBehavior.h"
class SinBehavior :
    public IBulletBehavior
{
public:
    void Update(Bullet& bullet) override;
    
};


