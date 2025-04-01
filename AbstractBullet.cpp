#include "AbstractBullet.h"
#include <cmath>

AbstractBullet::AbstractBullet(const Vector2<float>& position, int speed, int r, int color, int pattern, const Player& player)
	: CircleObject(position.GetterX(), position.GetterY(), r), _speed(speed), _color(color), _pattern(pattern), _playerPosition(player.GetterPosition()){

	switch (_pattern) {
	case 1:
		SetAngleToPlayer();
		break;
	case 2:
		SetAngleToPlayer();
		break;
	default:
		;
	}

}

void AbstractBullet::Update() {
	switch (_pattern) {
	case 1:
		break;
	case 2:
		SetAngleToPlayer();
		break;
	default:
		;
	}

	//���x���Z�b�g
	velocity.Setter(cosf(angle) * _speed, sinf(angle) * _speed);

	ShapeObject::Update();
}

void AbstractBullet::SetAngleToPlayer() {
	//player�Ǝ����̍����v�Z
	int difX = _playerPosition.GetterX() - position.GetterX();
	int difY = _playerPosition.GetterY() - position.GetterY();

	//�p�x���擾
	angle = atan2f(difX, difY);
}