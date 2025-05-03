#include "AbstractBullet.h"
#include "Macro.h"
#include "Define.h"
#include <cmath>

//DxLib�̓f�o�b�O�p

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
		ERR("�Ӑ}���Ă��Ȃ��e���p�^�[���ł�");
		break;
	}

	ShapeObject::Update();
	_cnt++;

}

void AbstractBullet::ShotStraight() {
	//�^����ꂽ�����ƃX�s�[�h�𑬓x�ɑ��
	_angle = _direction.GetterAngle();
	_velocity = _direction.Mult(_speed);
}

void AbstractBullet::ShotSin() {
	//�X�������Ȃ̂�sin�g�̏ꍇcos
	Vector2<float> velSin(_speed, 10*cosf(_cnt/10.0));
	_angle = _direction.GetterAngle();

	//direction�����ɌX����sin�g
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