#include "ShapeObject.h"

ShapeObject::ShapeObject(float posX, float posY) : position(posX, posY), velocity(0, 0), flag(0){
}

void ShapeObject::Move() {
	//���͂���Ă�������̒P�ʃx�N�g����speed���X�J���{�������̂����݈ʒu�ɑ���
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
	//2��flag���錾
	int temp = 1 << tFlag;
	if (value) {
		//�t���O�𗧂Ă�
		flag = flag | temp;
	}
	else {
		temp = 255 - temp;
		//�t���O��������
		flag = flag & temp;
	}
}