#include "OmniShotCommand.h"
#include "Define.h"
#include "BulletMgr.h"

OmniShotCommand::OmniShotCommand(Vector2<float> pos, float speed, int num, int color, eBulletSize size)
    : _pos(pos), _speed(speed), _numBullets(num), _color(color), _size(size) { }

void OmniShotCommand::Execute(BulletMgr& mgr) {
    for (int i = 0; i < _numBullets; ++i) {
        float angle = 2 * Define::PI * i / _numBullets;
        mgr.Set_StraightBullet(_size, _pos, angle, _speed, _color);
    }
}