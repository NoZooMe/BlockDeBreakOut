#include "Ball.h"
#include "Define.h"
#include "Keyboard.h"
#include <cmath>
#include <memory>
#include <DxLib.h>


Ball::Ball(int x, int y) : CircleObject(x, y, Define::BALL_RADIUS), rand(0), _acceleration(0){

}

void Ball::Initialize() {
	//ボールは最初は動いていない
	WaveFlag((int)fBall::_move, false);
}

void Ball::Finalize() {

}

void Ball::Update() {
	//加速度は入力に応じて(-5, 5)の範囲を上下する
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
		//スペースキーが押されたら待ち状態へ
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			WaveFlag((int)fBall::_wait, true);
		}
	}
	else {//離されたら解除
		_angle++;
		//急ごしらえradianと直線
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

//水平に当たった時に垂直に跳ねる判定
//blockのpositionを見て反射する方向を決める。もしもvelocityの方向が同じなら更に加算する
void Ball::ReflectBlock_Vertical(std::shared_ptr<RectangleObject> obj) {

	/*Blockの中心が自分より下にあるかどうかと自分の速度が正かどうかの条件によって結果を分岐させる*/
	bool conditionA = (obj->GetterPosY() + obj->GetterHeight() / 2 > _position.GetterY());
	bool conditionB = (_velocity.GetterY() > 0);

	if (conditionA == conditionB) {//速度を反転させる場合
		_velocity.SetterY(-_velocity.GetterY());
	}
	else {//速度を足す場合
		_velocity.SetterY(_velocity.GetterY() + obj->GetterVelY()/5);
	}


	//すり抜け防止
	if (conditionA) {//上から衝突
		_position.SetterY(obj->GetterPosY() - _r);
	}else {//下から衝突
		_position.SetterY(obj->GetterPosY() + obj->GetterHeight() + _r);
	}

	//少しランダム性を足す
	_velocity.SetterX(_velocity.GetterX() + rand);
	//速くする
	if (fabsf(_velocity.GetterY()) <= 15) {
		_velocity.SetterY(_velocity.GetterY() * 1.05);
	}
}

//別に今のままでもいいけど、角に当たった時の判定を別に用意するとか、反射にランダム性を持たせるとかも面白そう。
void Ball::ReflectBlock_Horizontal(std::shared_ptr<RectangleObject> obj) {
	//Blockの中心が自分より右かどうか
	bool conditionA = (obj->GetterPosX() + obj->GetterWidth() / 2 > _position.GetterX());
	bool conditionB = (_velocity.GetterX() > 0);

	if (conditionA == conditionB) {//速度を反転させる場合
		_velocity.SetterX(-_velocity.GetterX());
	}
	else {//速度を足す場合
		_velocity.SetterX(_velocity.GetterX() + obj->GetterVelX() / 5);
	}
	


	//すり抜け防止
	if (conditionA) {//左から衝突
		_position.SetterX(obj->GetterPosX() - _r);
	}
	else {//右から衝突
		_position.SetterX(obj->GetterPosX() + obj->GetterWidth() + _r);
	}

	_acceleration = 0;
	//少しランダム性+早くする
	_velocity.SetterY(_velocity.GetterY() + rand);
	if (fabsf(_velocity.GetterX()) < 15) {
	_velocity.SetterX(_velocity.GetterX() * 1.05);
	}
}

void Ball::ReflectFromSurface(const Segment& surface, const Vector2<float>& surfaceVelocity) {
	//壁の法線ベクトル
	Vector2<float> segVec = surface.GetterSegVector();
	//垂直ベクトルを2種類用意(2つのベクトルはsegVecに垂直だが向きが逆)
	Vector2<float> normal1(-segVec.GetterY(), segVec.GetterX());
	Vector2<float> normal2(segVec.GetterY(), -segVec.GetterX());

	//ボールの位置ベクトルと線分の法線が「近い向き」かどうかで選ぶ
	Vector2<float> toBall = _position - surface.GetterBegVector();
	
	Vector2<float> normal = 
		(toBall.DotProd(normal1) > 0) ? normal1.Norm() : normal2.Norm();

	//進行方向との関係で反射か加速かを決定
	float dot = _velocity.DotProd(normal);

	if (dot > 0) {
		//外向きに進んでるなら減速or吸収(or 加速)
		_velocity = _velocity + surfaceVelocity.Mult(0.2f);
	}
	else {
		//反射
		_velocity = _velocity - normal.Mult(2.0f * dot);
	}
	//位置補正:法線方向に小さく押し出す(すり抜け防止)
	float offset = _r;
	_position = _position + normal.Mult(offset);

	//軽いランダム性
	Vector2<float> tangent = Vector2<float>(normal.GetterY(), -normal.GetterX());//法線に直行
	_velocity = _velocity + tangent.Mult(rand);

	//速度制限(15)
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
	//xについての処理
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
		//下に落ちた時
		ShapeObject::WaveFlag((int)fBall::_out, true);
	}
}
