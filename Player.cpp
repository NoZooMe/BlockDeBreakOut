#include "Player.h"
#include <DxLib.h>
#include "Define.h"
#include "ImageManager.h"
#include "ResourceID.h"
#include "Keyboard.h"

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

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RSHIFT) >= 1) {
		
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_D) >= 1) {
		_angle = Define::PI / 4;
	}
	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_A) >= 1) {
		_angle = -Define::PI / 4;
	}
	else {
		_angle = 0;
	}
}

void Player::Draw() const {
	//無敵になったら点滅
	if (_mutekiCnt % 2 == 0) {
		ShapeObject::Draw(_position.GetterX(), _position.GetterY(), ImageManager::getIns()->getImage(toString(ResourceID::Player)));
		RectangleObject::Draw();
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
	if (_position.GetterX() - Define::PLAYER_WIDTH/2 < 0) {
		_position.Setter(GetterWidth() / 2.0f, _position.GetterY());
	}
	else if (_position.GetterX() + GetterWidth()/2 > Define::SCREEN_WIDTH) {
		_position.Setter(Define::SCREEN_WIDTH - GetterWidth()/2.0f, _position.GetterY());
	}

	//y座標について
	if (_position.GetterY() - Define::PLAYER_HEIGHT/2 < Define::SCREEN_HEIGHT * 3 / 5) {//画面上へは移動制御あり
		_position.Setter(_position.GetterX(), Define::SCREEN_HEIGHT*3/5 + GetterHeight()/2.0f);
	}
	else if (_position.GetterY() + GetterHeight()/2 > Define::SCREEN_HEIGHT) {
		_position.Setter(_position.GetterX(), Define::SCREEN_HEIGHT - GetterHeight()/2.0f);
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