#include "Player.h"
#include <DxLib.h>
#include "Define.h"

//Player::Player(float iniX, float iniY, IDethPlayer* iListener) : Rectangle(iniX, iniY, WIDTH, HEIGHT), listener(iListener), direction(0, 0) {
//
//}

Player::Player(float iniX, float iniY) : RectangleObject(iniX, iniY, Define::PLAYER_WIDTH, Define::PLAYER_HEIGHT), dirH(0), dirV(0), life(Define::PLAYER_LIFE) {
	
}

void Player::Initialize() {
	
}


void Player::Update() {
	if (!CheckFlag((int)fPlayer::_death)) {
		Check_Direciton();
		Set_Velocity();
		RectangleObject::Update();
		//��ʊO�����B�������O�ɏo�Ă����狭���I�ɖ߂�
		Check_Out();
	}
}

void Player::Draw() const {
	RectangleObject::Draw();
}

//�����Ă��������dirV��dirH��ω�.
void Player::Check_Direciton() {

	dirV = 0;
	dirH = 0;

	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		dirV = 1;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		dirV = -1;
	}

	if (CheckHitKey(KEY_INPUT_UP)) {
		dirH = -1;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		dirH = 1;
	}
}

//Velocity��direction�ŕω�����
void Player::Set_Velocity() {
	
	velocity.Setter(dirV, dirH);

	//�΂ߓ��͂Ȃ琳�K��
	if ((dirV!=0) && (dirH!=0)) {
		velocity = velocity.Norm();
	}
	velocity = velocity.Mult(speed);
	
}

void Player::SetPlayerFlag_OutVertical(bool value) {
	ShapeObject::WaveFlag((int)fPlayer::_outVertical, value);
}

void Player::SetPlayerFlag_OutHorizontal(bool value) {
	ShapeObject::WaveFlag((int)fPlayer::_outHorizontal, value);
}

void Player::SetPlayerFlag_Move(bool value) {
	ShapeObject::WaveFlag((int)fPlayer::_move, value);
}

void Player::SetPlayerFlag_Death(bool value) {
	ShapeObject::WaveFlag((int)fPlayer::_death, value);
}

void Player::Check_Out() {
	//��ʊO�Ȃ�ʂɑΉ�
	//x���W�ɂ���
	if (position.GetterX() < 0) {
		position.Setter(0, position.GetterY());
	}
	else if (position.GetterX() + GetterWidth() > Define::SCREEN_WIDTH) {
		position.Setter(Define::SCREEN_WIDTH - GetterWidth(), position.GetterY());
	}

	//y���W�ɂ���
	if (position.GetterY() < Define::SCREEN_HEIGHT * 3 / 5) {//��ʏ�ւ͈ړ����䂠��
		position.Setter(position.GetterX(), Define::SCREEN_HEIGHT*3/5);
	}
	else if (position.GetterY() + GetterHeight() > Define::SCREEN_HEIGHT) {
		position.Setter(position.GetterX(), Define::SCREEN_HEIGHT - GetterHeight());
	}
}

void Player::CallDecLife() {
	life--;
}

