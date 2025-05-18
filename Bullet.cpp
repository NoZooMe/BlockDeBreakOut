#include "Bullet.h"
#include "Macro.h"
#include "Define.h"
#include <cmath>

//DxLibはデバッグ用

Bullet::Bullet(const Vector2<float>& position, float angle, int speed, int pattern, int color, eBulletSize size)
	: CircleObject(position.GetterX(), position.GetterY(), 0), _speed(speed), _color(color), _pattern(pattern), _cnt(0){
	//全てのshapeObjectの角度はインスタンスで初期化されるべき。
	_angle = angle;

	//まずコンストラクタ使ってrを初期化してから代入し直すってものなんか変な気がするけど……。
	switch (size) {
	case eBulletSize::Small :
		_r = Define::BULLET_SIZE_SMALL;
		break;
	case eBulletSize::Midium:
		_r = Define::BULLET_SIZE_MIDIUM;
		break;
	case eBulletSize::Large:
		_r = Define::BULLET_SIZE_BIG;
		break;
	default:
		ERR("存在しない弾幕の大きさです");
		break;
	}

}

void Bullet::Initialize() {

}

void Bullet::Finalize() {

}

void Bullet::Update() {

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

void Bullet::Draw() const{
	CircleObject::Draw();
}

void Bullet::ShotStraight() {
	//与えられた方向とスピードを速度に代入
	//角度方向のベクトルを生成.
	_velocity = Vector2<float>(cosf(_angle), sinf(_angle)).Mult(_speed);
}

void Bullet::ShotSin() {
	//傾き方向なのでsin波の場合cos
	Vector2<float> velSin(_speed, 10 * cosf(_cnt / 10.0));

	//angle方向に傾けたsin波
	_velocity = velSin.RotateVector(_angle);
}

bool Bullet::CheckOut() {
	if (_position.GetterX() + GetterR() <= 0 || _position.GetterX() - GetterR() >= Define::SCREEN_WIDTH
		|| _position.GetterY() + GetterR() <= 0 || _position.GetterY() - GetterR() >= Define::SCREEN_HEIGHT ) {
		return true;
	}
	else {
		return false;
	}
}