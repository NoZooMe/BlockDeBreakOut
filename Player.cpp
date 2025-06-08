#include "Player.h"
#include <DxLib.h>
#include "Define.h"
#include "ImageManager.h"
#include "ResourceID.h"
#include "Keyboard.h"
#include "ComplexTransform.h"

Player::Player(float iniX, float iniY) : RectangleObject(iniX, iniY, Define::PLAYER_WIDTH, Define::PLAYER_HEIGHT), dirH(0), dirV(0),  _mutekiCnt(0) ,_t(0.0f), _dt(1.0f/60.0f), 
	_lastScore(0), _animationCnt(0), _speed(Define::PLAYER_SPEED){
}

void Player::Initialize() {
	WaveFlag(fPlayer::_onODE, false);
}


void Player::Update() {
	if (!CheckFlag(fPlayer::_death)) {
		Check_Direciton();
		//微分方程式による制御
		if (!CheckFlag(fPlayer::_onODE)) {
			Set_Velocity();
		}
		else {
			Set_VelocityODE(_t, _dt);
			//Set_VelocityLorenzA(_t, _dt);
		}
		
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

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_1) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Identity;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_2) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Inverse;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_3) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Sin;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_4) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Exp;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_5) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Conj;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_6) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Cos;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_7) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Tan;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_8) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Sinh;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_9) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Gamma;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_0) == 1) {
		ComplexTransform::mode = SpaceTransformMode::Zeta;
	}

	//Scoreが100を上回ったらライフ加算
	if (_lastScore < 100 && _status._score >= 100) {
		_status._life++;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LSHIFT) >= 1) {
		if (_width > Define::PLAYER_WIDTH / 2) {
			_width *= 0.9;
		}
		else {
			_width = Define::PLAYER_WIDTH / 2;
		}
	}
	else {
		if (_width < Define::PLAYER_WIDTH) {
			_animationCnt++;
			//30フレームでπ/2に
			float temp = Define::PI / 360.f * _animationCnt;
			_width = Define::DISPLAY_WIDTH * sinf(temp) + Define::PLAYER_WIDTH/2;

		}
		else {
			_width = Define::PLAYER_WIDTH;
			_animationCnt = 0;
		}
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL) >= 1) {
		_speed = Define::PLAYER_SPEED * 2;
	}
	else {
		_speed = Define::PLAYER_SPEED;
	}

	_lastScore = _status._score;
	_t++;
}

void Player::Draw() const {
	//無敵になったら点滅
	if (_mutekiCnt % 2 == 0) {
		
		Player::DrawExtendGraph();
		RectangleObject::Draw();
	}
	DrawFormatString(200, 200, Define::WHITE, "%d", _width);
	//位置表示
	//DrawFormatString(10, 50, GetColor(255, 255, 255), "pos=(%.1f, %.1f)", _position.GetterX(), _position.GetterY());
	//複素関数の名前表示
	DrawFormatString(0, 50, GetColor(255, 255, 255), "Transform: %s", ComplexTransform::ToString(ComplexTransform::mode).c_str());
}

//向いている方向でdirVとdirHを変化.
void Player::Check_Direciton() {

	dirV = 0;
	dirH = 0;

	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		dirH = 1;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		dirH = -1;
	}

	if (CheckHitKey(KEY_INPUT_UP)) {
		dirV = -1;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		dirV = 1;
	}
}

//Velocityはdirectionで変化する
void Player::Set_Velocity() {
	
	_velocity.Setter(dirH, dirV);

	//斜め入力なら正規化
	if ((dirV!=0) && (dirH!=0)) {
		_velocity = _velocity.Norm();
	}
	_velocity = _velocity.Mult(_speed);
	
}

void Player::Set_VelocityODE(float t, float dt) {
	Vector2<float> inputDir(0.0f, 0.0f);

	inputDir.Setter(dirH, dirV);

	//正規化　+　最大速度をかける
	if (inputDir.Abs() > 0.0f) {
		inputDir = inputDir.Norm().Mult(_speed);
	}


	//加速度に目標速度への追従を設定
	const float followRate = 3.0f;	//反応性
	_acceleration = (inputDir - _velocity).Mult(followRate * dt);
}

void Player::Set_VelocityLorenzA(float t, float dt) {
	float chaosStrength = 0.2f;
	float noiseX = chaosStrength * (rand() % 100 - 50); // -1.0~1.0
	float noiseY = chaosStrength * (rand() % 100 - 50);

	Vector2<float> chaosDir;
	chaosDir.Setter(noiseX, noiseY);

	Vector2<float> inputDir(dirH, dirV);
	//正規化　+　最大速度をかける
	if (inputDir.Abs() > 0.0f) {
		inputDir = inputDir.Norm().Mult(_speed);
	}

	// 入力+カオス
	Vector2<float> targetVel = inputDir + chaosDir;	//カオスを加える

	const float followRate = 3.0f;
	_acceleration = (targetVel - _velocity).Mult(followRate * dt);
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
	if (_position.GetterX() - _width/2 < 0) {
		_position.Setter(GetterWidth() / 2.0f, _position.GetterY());
		AdjustPosition();
	}
	else if (_position.GetterX() + _width/2 > Define::SCREEN_WIDTH) {
		_position.Setter(Define::SCREEN_WIDTH - GetterWidth()/2.0f, _position.GetterY());
		AdjustPosition();
	}

	//y座標について
	if (_position.GetterY() - _height/2 < Define::SCREEN_HEIGHT * 3 / 5) {//画面上へは移動制御あり
		_position.Setter(_position.GetterX(), Define::SCREEN_HEIGHT*3/5 + GetterHeight()/2.0f);
		AdjustPosition();
	}
	else if (_position.GetterY() + _height/2 > Define::SCREEN_HEIGHT) {
		_position.Setter(_position.GetterX(), Define::SCREEN_HEIGHT - GetterHeight()/2.0f);
		AdjustPosition();
	}
}

void Player::CallDecLife() {
	_status._life--;
}

void Player::CallIncLife() {
	_status._life++;
}

void Player::CallDecBomb() {
	_status._bomb--;
}

void Player::CallIncBomb() {
	_status._bomb++;
}

Vector2<float> Player::GetterPosition() const {

	float tempX = _position.GetterX();
	float tempY = _position.GetterY();

	Vector2<float> posVec(tempX, tempY);

	return posVec;
}

void Player::AdjustPosition() {
	//当たり判定は頂点で管理してるのでここを忘れると頂点の更新が遅れて当たり判定が少し飛び出す。
	float halfwidth = _width / 2.0f;
	float halfheight = _height / 2.0f;

	//左上、右上、右下、左下(時計回り)
	vertex[0] = Vector2<float>(_position.GetterX() - halfwidth, _position.GetterY() - halfheight);
	vertex[1] = Vector2<float>(_position.GetterX() + halfwidth, _position.GetterY() - halfheight);
	vertex[2] = Vector2<float>(_position.GetterX() + halfwidth, _position.GetterY() + halfheight);
	vertex[3] = Vector2<float>(_position.GetterX() - halfwidth, _position.GetterY() + halfheight);

	//右辺
	vertSide1.UpdateSegment(vertex[0], vertex[3]);
	//左辺
	vertSide2.UpdateSegment(vertex[1], vertex[2]);
	//上辺
	horiSide1.UpdateSegment(vertex[0], vertex[1]);
	//下辺
	horiSide2.UpdateSegment(vertex[3], vertex[2]);
}

bool Player::TryUseBomb() {
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1 && _status._bomb > 0) {
		
		return true;
	}
	return false;
}

void Player::DrawExtendGraph() const {

	double extendRate = static_cast<double>(_width) / static_cast<double>(Define::PLAYER_WIDTH);
	int x = static_cast<int>(_position.GetterX());
	int y = static_cast<int>(_position.GetterY());

	DrawRotaGraph3(x, y, Define::PLAYER_WIDTH/2, _height/2, extendRate, 1.0, _angle,
		ImageManager::getIns()->getImage(toString(ResourceID::Player)), false);
}