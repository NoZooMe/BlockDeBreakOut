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
		ERR("�Ӑ}���Ă��Ȃ��e���p�^�[���ł�");
		break;
	}

}

void AbstractBullet::Update() {

	ShapeObject::Update();
}

void AbstractBullet::ShotStraight() {
	//�^����ꂽ�����ƃX�s�[�h�𑬓x�ɑ��
	velocity = _direction.Mult(_speed);

}

void AbstractBullet::ShotSin() {
	Vector2<float> velSin(_speed, sinf(_speed));
	float angle = _direction.GetterAngle();
	
	//direction�����ɌX����sin�g
	velocity = velSin.RotateVector(angle);
}