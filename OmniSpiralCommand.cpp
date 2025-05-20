#include "OmniSpiralCommand.h"
#include "BulletMgr.h"
#include "SpiralBehavior.h"
#include "Define.h"
#include <memory>

OmniSpiralCommand::OmniSpiralCommand(Vector2<float> pos, int numBullets, float speed, int color, eBulletSize size) : _pos(pos), _numBullets(numBullets), _speed(speed), _color(color), _size(size){

}


void OmniSpiralCommand::Execute(BulletMgr& mgr) {
	const float baseAngle = 0.0f;
	const float angleStep = 2.0f * Define::PI / _numBullets;	//_numBullets‰ñ“]Žq

	for (int i = 0; i < _numBullets; ++i) {
		float angle = baseAngle + angleStep * i;
		mgr.AddBullet(_size, _pos, angle, _speed, _color, std::make_shared<SpiralBehavior>());
	}
}