#include "Bullet.h"
#include "Macro.h"
#include "Define.h"
#include <cmath>

//DxLib�̓f�o�b�O�p

Bullet::Bullet(const Vector2<float>& position, float angle, int speed, int pattern, int color, eBulletSize size)
	: CircleObject(position.GetterX(), position.GetterY(), 0), _speed(speed), _color(color), _pattern(pattern), _cnt(0){
	//�S�Ă�shapeObject�̊p�x�̓C���X�^���X�ŏ����������ׂ��B
	_angle = angle;

	//�܂��R���X�g���N�^�g����r�����������Ă��������������Ă��̂Ȃ񂩕ςȋC�����邯�ǁc�c�B
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
		ERR("���݂��Ȃ��e���̑傫���ł�");
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
		ERR("�Ӑ}���Ă��Ȃ��e���p�^�[���ł�");
		break;
	}

	ShapeObject::Update();
	_cnt++;

}

void Bullet::Draw() const{
	CircleObject::Draw();
}

void Bullet::ShotStraight() {
	//�^����ꂽ�����ƃX�s�[�h�𑬓x�ɑ��
	//�p�x�����̃x�N�g���𐶐�.
	_velocity = Vector2<float>(cosf(_angle), sinf(_angle)).Mult(_speed);
}

void Bullet::ShotSin() {
	//�X�������Ȃ̂�sin�g�̏ꍇcos
	Vector2<float> velSin(_speed, 10 * cosf(_cnt / 10.0));

	//angle�����ɌX����sin�g
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