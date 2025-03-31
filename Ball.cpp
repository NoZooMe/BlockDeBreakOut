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
		position.Setter(playerX, playerY);
		//�X�y�[�X�L�[�������ꂽ��҂���Ԃ�
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			WaveFlag((int)fBall::_wait, true);
		}
	}
	else {//�����ꂽ�����
		angle++;
		//�}�����炦radian�ƒ���
		float radian = ((float)(angle % 360) / 180 * Define::PI) * 2 ;
		DrawLine(position.GetterX(), position.GetterY(), position.GetterX() + 100*cosf(radian), position.GetterY() - fabsf(100*sinf(radian)), Define::GREEN, 0);
		if (Keyboard::getIns()->getReleasingCount(KEY_INPUT_SPACE) == 1) {			
			velocity.Setter(SPEED*cosf(radian), -fabsf(SPEED*sinf(radian)));
			WaveFlag((int)fBall::_move, true);
			WaveFlag((int)fBall::_wait, false);
			angle = 0;
		}

	}

	
}

void Ball::Draw() const {
	CircleObject::Draw();
}

//block��position�����Ĕ��˂�����������߂�B������velocity�̕����������Ȃ�X�ɉ��Z����
void Ball::ReflectBlock_Vertical(std::shared_ptr<RectangleObject> obj) {

	/*Block�̒��S��������艺�ɂ��邩�ǂ����Ǝ����̑��x�������ǂ����̏����ɂ���Č��ʂ𕪊򂳂���*/
	bool conditionA = (obj->GetterPosY() + obj->GetterHeight() / 2 > position.GetterY());
	bool conditionB = (velocity.GetterY() > 0);

	if (conditionA == conditionB) {//���x�𔽓]������ꍇ
		velocity.SetterY(-velocity.GetterY());
	}
	else {//���x�𑫂��ꍇ
		velocity.SetterY(velocity.GetterY() + obj->GetterVelY()/5);
	}

	//���蔲���h�~
	if (conditionA) {//�ォ��Փ�
		position.SetterY(obj->GetterPosY() - r);
	}else {//������Փ�
		position.SetterY(obj->GetterPosY() + obj->GetterHeight() + r);
	}
}

//�ʂɍ��̂܂܂ł��������ǁA�p�ɓ����������̔����ʂɗp�ӂ���Ƃ��A���˂Ƀ����_��������������Ƃ����ʔ������B
void Ball::ReflectBlock_Horizontal(std::shared_ptr<RectangleObject> obj) {
	//Block�̒��S���������E���ǂ���
	bool conditionA = (obj->GetterPosX() + obj->GetterWidth() / 2 > position.GetterX());
	bool conditionB = (velocity.GetterX() > 0);

	if (conditionA == conditionB) {//���x�𔽓]������ꍇ
		velocity.SetterX(-velocity.GetterX());
	}
	else {//���x�𑫂��ꍇ
		velocity.SetterX(velocity.GetterX() + obj->GetterVelX() / 5);
	}

	//���蔲���h�~
	if (conditionA) {//������Փ�
		position.SetterX(obj->GetterPosX() - r);
	}
	else {//�E����Փ�
		position.SetterX(obj->GetterPosX() + obj->GetterWidth() + r);
	}
}

void Ball::ReflectWall_Horizontal() {
	velocity.SetterX(-velocity.GetterX());
}

void Ball::ReflectWall_Vertical() {
	velocity.SetterY(-velocity.GetterY());
}

void Ball::Check_Out() {
	//x�ɂ��Ă̏���
	if (GetterPosX() - GetterR() < 0) {
		position.Setter(GetterR(), GetterPosY());
		ReflectWall_Horizontal();
	}
	else if(GetterPosX() + GetterR() > Define::SCREEN_WIDTH){
		position.Setter(Define::SCREEN_WIDTH - GetterR(), GetterPosY());
		ReflectWall_Horizontal();
	}

	if (GetterPosY() - GetterR() < 0) {
		position.Setter(GetterPosX(), GetterR());
		ReflectWall_Vertical();
	}
	else if (GetterPosY() - GetterR() > Define::SCREEN_HEIGHT) {
		//���ɗ�������
		ShapeObject::WaveFlag((int)fBall::_out, true);
	}
}
