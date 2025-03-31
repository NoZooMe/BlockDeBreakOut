#include "Ball.h"
#include "DxLib.h"
#include "Define.h"
#include "Keyboard.h"
#include <cmath>
#include <memory>


Ball::Ball(int x, int y) : CircleObject(x, y, Define::BALL_RADIUS){

}

void Ball::Initialize() {
	//ボールは最初は動いていない
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
		//スペースキーが押されたら待ち状態へ
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			WaveFlag((int)fBall::_wait, true);
		}
	}
	else {//離されたら解除
		angle++;
		//急ごしらえradianと直線
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

//blockのpositionを見て反射する方向を決める。もしもvelocityの方向が同じなら更に加算する
void Ball::ReflectBlock_Vertical(std::shared_ptr<RectangleObject> obj) {

	/*Blockの中心が自分より下にあるかどうかと自分の速度が正かどうかの条件によって結果を分岐させる*/
	bool conditionA = (obj->GetterPosY() + obj->GetterHeight() / 2 > position.GetterY());
	bool conditionB = (velocity.GetterY() > 0);

	if (conditionA == conditionB) {//速度を反転させる場合
		velocity.SetterY(-velocity.GetterY());
	}
	else {//速度を足す場合
		velocity.SetterY(velocity.GetterY() + obj->GetterVelY()/5);
	}

	//すり抜け防止
	if (conditionA) {//上から衝突
		position.SetterY(obj->GetterPosY() - r);
	}else {//下から衝突
		position.SetterY(obj->GetterPosY() + obj->GetterHeight() + r);
	}
}

//別に今のままでもいいけど、角に当たった時の判定を別に用意するとか、反射にランダム性を持たせるとかも面白そう。
void Ball::ReflectBlock_Horizontal(std::shared_ptr<RectangleObject> obj) {
	//Blockの中心が自分より右かどうか
	bool conditionA = (obj->GetterPosX() + obj->GetterWidth() / 2 > position.GetterX());
	bool conditionB = (velocity.GetterX() > 0);

	if (conditionA == conditionB) {//速度を反転させる場合
		velocity.SetterX(-velocity.GetterX());
	}
	else {//速度を足す場合
		velocity.SetterX(velocity.GetterX() + obj->GetterVelX() / 5);
	}

	//すり抜け防止
	if (conditionA) {//左から衝突
		position.SetterX(obj->GetterPosX() - r);
	}
	else {//右から衝突
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
	//xについての処理
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
		//下に落ちた時
		ShapeObject::WaveFlag((int)fBall::_out, true);
	}
}
