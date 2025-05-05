#include "Player.h"
#include <DxLib.h>
#include "Define.h"
#include "Image.h"
#include "Keyboard.h"

//Player::Player(float iniX, float iniY, IDethPlayer* iListener) : Rectangle(iniX, iniY, WIDTH, HEIGHT), listener(iListener), direction(0, 0) {
//
//}

Player::Player(float iniX, float iniY) : RectangleObject(iniX, iniY, Define::PLAYER_WIDTH, Define::PLAYER_HEIGHT), dirH(0), dirV(0), life(Define::PLAYER_LIFE), _mutekiCnt(0) {
	
}

void Player::Initialize() {
	
}


void Player::Update() {
	if (!CheckFlag(fPlayer::_death)) {
		Check_Direciton();
		Set_Velocity();
		RectangleObject::Update();
		//画面外処理。もしも外に出ていたら強制的に戻す
		Check_Out();

		//無敵フラグがオンならcntを増やす
		if (CheckFlag(fPlayer::_muteki)) {
			_mutekiCnt++;
			if (_mutekiCnt%60 == 0) {
				ShapeObject::WaveFlag(fPlayer::_muteki, false);
			}
		}
		else {
			_mutekiCnt = 0;
		}
	}

	/*
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_S) >= 1) {
		_angle = Define::PI / 2;
	}
	else {
		_angle = 0;
	}
	*/
}

void Player::Draw() const {
	//無敵になったら点滅
	if (_mutekiCnt % 2 == 0) {
		//中心座標を指定しているが……。
		ShapeObject::Draw(_position.GetterX()+Define::PLAYER_WIDTH/2, _position.GetterY()+Define::PLAYER_HEIGHT/2, Image::getIns()->getPlayer());
	}
}

//向いている方向でdirVとdirHを変化.
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

//Velocityはdirectionで変化する
void Player::Set_Velocity() {
	
	_velocity.Setter(dirV, dirH);

	//斜め入力なら正規化
	if ((dirV!=0) && (dirH!=0)) {
		_velocity = _velocity.Norm();
	}
	_velocity = _velocity.Mult(speed);
	
}

void Player::SetPlayerFlag_OutVertical(bool value) {
	ShapeObject::WaveFlag(fPlayer::_outVertical, value);
}

void Player::SetPlayerFlag_OutHorizontal(bool value) {
	ShapeObject::WaveFlag(fPlayer::_outHorizontal, value);
}

void Player::SetPlayerFlag_Move(bool value) {
	ShapeObject::WaveFlag(fPlayer::_move, value);
}

void Player::SetPlayerFlag_Death(bool value) {
	ShapeObject::WaveFlag(fPlayer::_death, value);
}

void Player::DamagePlayer() {
	ShapeObject::WaveFlag(fPlayer::_muteki, true);
}

bool Player::isDamaged() const {
	return ShapeObject::CheckFlag(fPlayer::_muteki);
}

void Player::RotateLeft() {
	_angle--;

	if (_angle == -90) {
		_angle = 0;
	}
}

void Player::RotateRight() {
	_angle++;

	if (_angle == 90) {
		_angle = 0;
	}
}

void Player::Check_Out() {
	//画面外なら個別に対応
	//x座標について
	if (_position.GetterX() < 0) {
		_position.Setter(0, _position.GetterY());
	}
	else if (_position.GetterX() + GetterWidth() > Define::SCREEN_WIDTH) {
		_position.Setter(Define::SCREEN_WIDTH - GetterWidth(), _position.GetterY());
	}

	//y座標について
	if (_position.GetterY() < Define::SCREEN_HEIGHT * 3 / 5) {//画面上へは移動制御あり
		_position.Setter(_position.GetterX(), Define::SCREEN_HEIGHT*3/5);
	}
	else if (_position.GetterY() + GetterHeight() > Define::SCREEN_HEIGHT) {
		_position.Setter(_position.GetterX(), Define::SCREEN_HEIGHT - GetterHeight());
	}
}

void Player::CallDecLife() {
	life--;
}

Vector2<float> Player::GetterPosition() const {

	float tempX = _position.GetterX() + Define::PLAYER_WIDTH/2;
	float tempY = _position.GetterY() + Define::PLAYER_HEIGHT/2;

	Vector2<float> posVec(tempX, tempY);

	return posVec;
}