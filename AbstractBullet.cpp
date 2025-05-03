#include "AbstractBullet.h"
#include "Macro.h"
#include "Define.h"
#include <cmath>

//DxLibはデバッグ用

AbstractBullet::AbstractBullet(const Vector2<float>& position, const Vector2<float>& direction, int speed, int pattern, int color, int r)
	: CircleObject(position.GetterX(), position.GetterY(), r), _speed(speed), _color(color), _pattern(pattern), _direction((direction - _position).Norm()), _cnt(0){
}

void AbstractBullet::Update() {

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

	ShapeObject::Update();
	_cnt++;

}

void AbstractBullet::ShotStraight() {
	//与えられた方向とスピードを速度に代入
	_angle = _direction.GetterAngle();
	_velocity = _direction.Mult(_speed);
}

void AbstractBullet::ShotSin() {
	//傾き方向なのでsin波の場合cos
	Vector2<float> velSin(_speed, 10*cosf(_cnt/10.0));
	_angle = _direction.GetterAngle();

	//direction方向に傾けたsin波
	_velocity = velSin.RotateVector(_angle);
}

bool AbstractBullet::CheckOut() {
	if (_position.GetterX() + GetterR() <= 0 || _position.GetterX() - GetterR() >= Define::SCREEN_WIDTH
		|| _position.GetterY() + GetterR() <= 0 || _position.GetterY() - GetterR() >= Define::SCREEN_HEIGHT ) {
		return true;
	}
	else {
		return false;
	}
}