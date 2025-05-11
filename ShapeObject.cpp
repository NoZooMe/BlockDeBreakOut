#include "ShapeObject.h"
#include <DxLib.h>

ShapeObject::ShapeObject(float posX, float posY) : _position(posX, posY), _velocity(0, 0), _flag(0){
}

void ShapeObject::Move() {
	_position = _position + _velocity;
}

void ShapeObject::Update() {
	Move();
}


bool ShapeObject::CheckFlag(const int tFlag) const {
	if ((_flag & (1 << tFlag)) == (1 << tFlag)) {
		return true;
	}
	else {
		return false;
	}
}

void ShapeObject::WaveFlag(int tFlag, bool value) {
	//2のflag乗を宣言
	int temp = 1 << tFlag;
	if (value) {
		//フラグを立てる
		_flag = _flag | temp;
	}
	else {
		temp = 255 - temp;
		//フラグを下げる
		_flag = _flag & temp;
	}
}

void ShapeObject::SetOnFlag(int tFlag) {
	WaveFlag(tFlag, true);
}

void ShapeObject::Draw(float x, float y, int handle) const {
	DrawRotaGraphF(x, y, 1.0, _angle, handle, TRUE);
}