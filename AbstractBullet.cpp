#include "AbstractBullet.h"
#include "Macro.h"
#include <cmath>

AbstractBullet::AbstractBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int pattern, int color, int r)
	: CircleObject(position.GetterX(), position.GetterY(), r), _speed(speed), _color(color), _pattern(pattern), _direction(direction.Norm()){
	
	switch (_pattern) {
	case 1:
		ShotStraight();
		break;
	case 2:
		ShotSin();
		break;
	default:
		ERR("意図していない弾幕パターンです");
		break;
	}

}

void AbstractBullet::Update() {

	ShapeObject::Update();
}

void AbstractBullet::ShotStraight() {
	//与えられた方向とスピードを速度に代入
	velocity = _direction.Mult(_speed);

}

void AbstractBullet::ShotSin() {
	Vector2<float> velSin(_speed, sinf(_speed));
	float angle = _direction.GetterAngle();
	
	//direction方向に傾けたsin波
	velocity = velSin.RotateVector(angle);
}