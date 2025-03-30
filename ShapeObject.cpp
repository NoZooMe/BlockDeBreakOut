#include "ShapeObject.h"

ShapeObject::ShapeObject(float posX, float posY) : position(posX, posY), velocity(0, 0), flag(0){
}

void ShapeObject::Move() {
	//入力されている方向の単位ベクトルにspeedをスカラ倍したものを現在位置に足す
	position = position + velocity;
}

void ShapeObject::Update() {
	Move();
}


bool ShapeObject::CheckFlag(const int tFlag) const {
	if ((flag & (1 << tFlag)) == (1 << tFlag)) {
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
		flag = flag | temp;
	}
	else {
		temp = 255 - temp;
		//フラグを下げる
		flag = flag & temp;
	}
}