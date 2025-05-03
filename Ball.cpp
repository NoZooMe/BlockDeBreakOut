#include "Ball.h"
#include "DxLib.h"
#include "Define.h"
#include "Keyboard.h"
#include <cmath>
#include <memory>


Ball::Ball(int x, int y) : CircleObject(x, y, Define::BALL_RADIUS){

}

void Ball::Initialize() {
	//�{�[���͍ŏ��͓����Ă��Ȃ�
	WaveFlag((int)fBall::_move, false);
}

void Ball::Finalize() {

}

void Ball::Update() {
	ShapeObject::Update();
	Check_Out();
}

void Ball::Update(float playerX, float playerY) {
	if (!CheckFlag((int)fBall::_wait)) {
		_position.Setter(playerX, playerY);
		//�X�y�[�X�L�[�������ꂽ��҂���Ԃ�
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			WaveFlag((int)fBall::_wait, true);
		}
	}
	else {//�����ꂽ�����
		_angle++;
		//�}�����炦radian�ƒ���
		float radian = ((float)(static_cast<int>(_angle) % 360) / 180 * Define::PI) * 2 ;
		DrawLine(_position.GetterX(), _position.GetterY(), _position.GetterX() + 100*cosf(radian), _position.GetterY() - fabsf(100*sinf(radian)), Define::GREEN, 0);
		if (Keyboard::getIns()->getReleasingCount(KEY_INPUT_SPACE) == 1) {			
			_velocity.Setter(SPEED*cosf(radian), -fabsf(SPEED*sinf(radian)));
			WaveFlag((int)fBall::_move, true);
			WaveFlag((int)fBall::_wait, false);
			_angle = 0;
		}

	}

	
}

void Ball::Draw() const {
	CircleObject::Draw();
}

//block��position�����Ĕ��˂�����������߂�B������velocity�̕����������Ȃ�X�ɉ��Z����
void Ball::ReflectBlock_Vertical(std::shared_ptr<RectangleObject> obj) {

	/*Block�̒��S��������艺�ɂ��邩�ǂ����Ǝ����̑��x�������ǂ����̏����ɂ���Č��ʂ𕪊򂳂���*/
	bool conditionA = (obj->GetterPosY() + obj->GetterHeight() / 2 > _position.GetterY());
	bool conditionB = (_velocity.GetterY() > 0);

	if (conditionA == conditionB) {//���x�𔽓]������ꍇ
		_velocity.SetterY(-_velocity.GetterY());
	}
	else {//���x�𑫂��ꍇ
		_velocity.SetterY(_velocity.GetterY() + obj->GetterVelY()/5);
	}

	//���蔲���h�~
	if (conditionA) {//�ォ��Փ�
		_position.SetterY(obj->GetterPosY() - r);
	}else {//������Փ�
		_position.SetterY(obj->GetterPosY() + obj->GetterHeight() + r);
	}
}

//�ʂɍ��̂܂܂ł��������ǁA�p�ɓ����������̔����ʂɗp�ӂ���Ƃ��A���˂Ƀ����_��������������Ƃ����ʔ������B
void Ball::ReflectBlock_Horizontal(std::shared_ptr<RectangleObject> obj) {
	//Block�̒��S���������E���ǂ���
	bool conditionA = (obj->GetterPosX() + obj->GetterWidth() / 2 > _position.GetterX());
	bool conditionB = (_velocity.GetterX() > 0);

	if (conditionA == conditionB) {//���x�𔽓]������ꍇ
		_velocity.SetterX(-_velocity.GetterX());
	}
	else {//���x�𑫂��ꍇ
		_velocity.SetterX(_velocity.GetterX() + obj->GetterVelX() / 5);
	}

	//���蔲���h�~
	if (conditionA) {//������Փ�
		_position.SetterX(obj->GetterPosX() - r);
	}
	else {//�E����Փ�
		_position.SetterX(obj->GetterPosX() + obj->GetterWidth() + r);
	}
}

void Ball::ReflectWall_Horizontal() {
	_velocity.SetterX(-_velocity.GetterX());
}

void Ball::ReflectWall_Vertical() {
	_velocity.SetterY(-_velocity.GetterY());
}

void Ball::Check_Out() {
	//x�ɂ��Ă̏���
	if (GetterPosX() - GetterR() < 0) {
		_position.Setter(GetterR(), GetterPosY());
		ReflectWall_Horizontal();
	}
	else if(GetterPosX() + GetterR() > Define::SCREEN_WIDTH){
		_position.Setter(Define::SCREEN_WIDTH - GetterR(), GetterPosY());
		ReflectWall_Horizontal();
	}

	if (GetterPosY() - GetterR() < 0) {
		_position.Setter(GetterPosX(), GetterR());
		ReflectWall_Vertical();
	}
	else if (GetterPosY() - GetterR() > Define::SCREEN_HEIGHT) {
		//���ɗ�������
		ShapeObject::WaveFlag((int)fBall::_out, true);
	}
}
