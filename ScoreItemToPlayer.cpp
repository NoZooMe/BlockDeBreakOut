#include "ScoreItemToPlayer.h"

ScoreItemToPlayer::ScoreItemToPlayer(float x, float y) : ScoreItem(x, y) , _cnt(0), _toVelocity(0, 0){
	//45“x‚©‚ç135“x
	int angle = rand() % 90 + 45;
	float radian = Define::PI / 180.0f * static_cast<float>(angle);
	_velocity = Vector2<float>(cosf(radian), -sinf(radian)).Mult(5);
	_acceleration = Vector2<float>(0, 0.1f);
	_width = Define::ITEM_WIDTH / 3;
	_height = Define::ITEM_HEIGHT / 3;
	_valueScore = Define::ITEM_SCORE_VALUE/100;
}

void ScoreItemToPlayer::Update() {
	AbstractItem::Update();
	_cnt++;
	if (_cnt >= Define::ITEM_FLOATING_TIME * 60) {
		_acceleration = Vector2<float>(0, 0);
		_velocity = _toVelocity;
	}
}


void ScoreItemToPlayer::SetVelocity(const Vector2<float>& PlayerPosition) {
	if ((PlayerPosition - _position).Abs() > 0.1f) {
		_toVelocity = (PlayerPosition - _position).Norm().Mult(50);
	}
	else {
		_toVelocity = Vector2<float>(0, 0);
	}
	
}