#include "Bullet.h"
#include "Macro.h"
#include "Define.h"
#include "ComplexTransform.h"
#include "DxLib.h"
#include <cmath>

Bullet::Bullet(const Vector2<float>& position, float angle, int speed, std::shared_ptr<IBulletBehavior> b, int color, eBulletSize size)
	: CircleObject(position.GetterX(), position.GetterY(), 0), _speed(speed), _color(color),  _cnt(0), _behavior(b), _euclidPosition(_position){
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
	_behavior->Update(*this);	// _velocity���X�V����

	//���[�N���b�h��ԏ�ňړ�
	_euclidPosition = _euclidPosition + _velocity;
	

	//���S�ʒu
	float cx = Define::SCREEN_WIDTH / 2.0f;
	float cy = Define::SCREEN_HEIGHT / 2.0f;

	float scale = 80.0f;

	// ��ʍ��W �� ���f���W�i���S�����_�j
	std::complex<float> z((_euclidPosition.GetterX() - cx) / scale,
		-(_euclidPosition.GetterY() - cy) / scale);  // y�����]

	// 2. ���� z ��␳�i�ɉ���j
	const float epsilon = 1e-2f;
	if (std::abs(z) < epsilon) {
		float theta = std::arg(z);
		z = std::polar(epsilon, theta); // �Â̋����ɒu��������
	}

	// 3. ���f�ϊ� f(z)
	std::complex<float> z_trans = ComplexTransform::Apply(z);

	// 4. f(z) ���傫������Ƃ��� log�X�P�[�� or clamp
	float mag = std::abs(z_trans);
	float maxMag = 10.0f;  // �X�P�[���O�̍ő勖�e�l�i�����j

	if (mag > maxMag) {
		// log�X�P�[�����O�Ŏ��߂�i���炩�j
		float scaledMag = std::log(1.0f + mag);
		z_trans = std::polar(scaledMag, std::arg(z_trans));
	}

	
	//�ϊ���̈ʒu�ɔ��f(ShapeObject�̕`��E�����蔻��p)

	_position.Setter(cx + z_trans.real() * scale, cy - z_trans.imag() * scale);

	ShapeObject::Update();
	_cnt++;

}

void Bullet::Draw() const{
	CircleObject::Draw();
}

bool Bullet::CheckOut() {
	if (_position.GetterX() + GetterR() <= 0 || _position.GetterX() - GetterR() >= Define::SCREEN_WIDTH
		|| _position.GetterY() + GetterR() <= 0 || _position.GetterY() - GetterR() >= Define::SCREEN_HEIGHT ) {
		return true;
	}
	else if(_euclidPosition.GetterX() + GetterR() <= 0 || _euclidPosition.GetterX() - GetterR() >= Define::SCREEN_WIDTH
		|| _euclidPosition.GetterY() + GetterR() <= 0 || _euclidPosition.GetterY() - GetterR() >= Define::SCREEN_HEIGHT)
	{
		return true;
	}
	else 
	{
		return false;
	}
}