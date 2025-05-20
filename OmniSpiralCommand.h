#pragma once
#include "BulletCommand.h"
#include "Vector2.h"
#include "eBulletSize.h"
class OmniSpiralCommand :
    public BulletCommand
{
public:

    OmniSpiralCommand(Vector2<float> pos, int numBullets, float speed, int color, eBulletSize size);

    void Execute(BulletMgr& mgr) override;

private:
    Vector2<float> _pos;
    int _numBullets;
    float _speed;
    int _color;
    eBulletSize _size;
};

