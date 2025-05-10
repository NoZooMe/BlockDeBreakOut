#include "Ball.h"
#include "Define.h"
#include "Keyboard.h"
#include <cmath>
#include <memory>
#include <DxLib.h>


Ball::Ball(int x, int y) : CircleObject(x, y, Define::BALL_RADIUS), rand(0), _acceleration(0){

}

void Ball::Initialize() {
	//�{�[���͍ŏ��͓����Ă��Ȃ�
	WaveFlag((int)fBall::_move, false);
}

void Ball::Finalize() {

}

void Ball::Update() {
	//�����x�͓��͂ɉ�����(-5, 5)�͈̔͂��㉺����
	/*if (Keyboard::getIns()->getPressingCount(KEY_INPUT_A) != 0) {
		if (_acceleration >= -1.1) {
			_acceleration -= 0.001;
		}
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_D) != 0) {
		if (_acceleration <= 1.1) {
			_acceleration += 0.001;
		}
	}*/

	if (rand < 0.5) {
		rand += 0.01;
	}
	else {
		rand = -0.5;
	}

	_velocity.SetterX(_velocity.GetterX() + _acceleration);

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
	DrawFormatString(0, 640, GetColor(255, 255, 255), "%f", _velocity.GetterY());
}

//�����ɓ����������ɐ����ɒ��˂锻��
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
		_position.SetterY(obj->GetterPosY() - _r);
	}else {//������Փ�
		_position.SetterY(obj->GetterPosY() + obj->GetterHeight() + _r);
	}

	//���������_�����𑫂�
	_velocity.SetterX(_velocity.GetterX() + rand);
	//��������
	if (fabsf(_velocity.GetterY()) <= 15) {
		_velocity.SetterY(_velocity.GetterY() * 1.05);
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
		_position.SetterX(obj->GetterPosX() - _r);
	}
	else {//�E����Փ�
		_position.SetterX(obj->GetterPosX() + obj->GetterWidth() + _r);
	}

	_acceleration = 0;
	//���������_����+��������
	_velocity.SetterY(_velocity.GetterY() + rand);
	if (fabsf(_velocity.GetterX()) < 15) {
	_velocity.SetterX(_velocity.GetterX() * 1.05);
	}
}

void Ball::ReflectFromSurface(const Segment& surface, const Vector2<float>& surfaceVelocity) {
	//�ǂ̖@���x�N�g��
	Vector2<float> segVec = surface.GetterSegVector();
	//�����x�N�g����2��ޗp��(2�̃x�N�g����segVec�ɐ��������������t)
	Vector2<float> normal1(-segVec.GetterY(), segVec.GetterX());
	Vector2<float> normal2(segVec.GetterY(), -segVec.GetterX());

	//�{�[���̈ʒu�x�N�g���Ɛ����̖@�����u�߂������v���ǂ����őI��
	Vector2<float> toBall = _position - surface.GetterBegVector();
	
	Vector2<float> normal = 
		(toBall.DotProd(normal1) > 0) ? normal1.Norm() : normal2.Norm();

	//�i�s�����Ƃ̊֌W�Ŕ��˂�������������
	float dot = _velocity.DotProd(normal);

	if (dot > 0) {
		//�O�����ɐi��ł�Ȃ猸��or�z��(or ����)
		_velocity = _velocity + surfaceVelocity.Mult(0.2f);
	}
	else {
		//����
		_velocity = _velocity - normal.Mult(2.0f * dot);
	}
	//�ʒu�␳:�@�������ɏ����������o��(���蔲���h�~)
	float offset = _r;
	_position = _position + normal.Mult(offset);

	//�y�������_����
	Vector2<float> tangent = Vector2<float>(normal.GetterY(), -normal.GetterX());//�@���ɒ��s
	_velocity = _velocity + tangent.Mult(rand);

	//���x����(15)
	if (_velocity.Abs() < 15.0f) {
		_velocity = _velocity.Mult(1.05f);
	}


}

void Ball::ReflectWall_Horizontal() {
	_velocity.SetterX(-_velocity.GetterX());

	_acceleration = 0;
}

void Ball::ReflectWall_Vertical() {
	_velocity.SetterY(-_velocity.GetterY());

	_acceleration = 0;
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
