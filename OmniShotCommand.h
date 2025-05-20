#pragma once
#include "BulletCommand.h"
#include "Vector2.h"
#include "eBulletSize.h"
class OmniShotCommand :
    public BulletCommand
{
public:
    OmniShotCommand(Vector2<float> pos, float speed, int num, int color, eBulletSize size);
    void Execute(BulletMgr& mgr) override;

private:
    Vector2<float> _pos;
    float _speed;
    int _numBullets;
    int _color;
    eBulletSize _size;
};

