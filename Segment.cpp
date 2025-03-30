#include "Segment.h"



Segment::Segment(float beginX, float beginY, float endX, float endY) : begin(beginX, beginY), end(endX, endY), segment(endX - beginX, endY - beginY){
}

void Segment::UpdateSegment(float beginX, float beginY, float endX, float endY) {
	begin.Setter(beginX, beginY);
	end.Setter(endX, endY);
	segment.Setter(endX - beginX, endY - beginY);
}


bool Segment::CheckOnPoint(const Vector2<float>& point) const{
	
	//���W����.����Ă����疳���Ă�����
	//�_�̍��W����
	int x = point.GetterX();
	int y = point.GetterY();

	//�����̍��W����
	int x1 = begin.GetterX();
	int y1 = begin.GetterY();
	int x2 = end.GetterX();
	int y2 = end.GetterY();

	//�p�����[�^��錾
	int tx, ty;

	//�����̌X����0�܂��͖����ꍇ�͌ʂŌv�Z
	if (x1 == x2) {
		ty = y2 - y1;
		tx = ty;
	}
	else if (y1 == y2) {
		tx = x2 - x1;
		ty = tx;
	}
	else {
		tx = (x - x1) / (x2 - x1);
		ty = (y - y1) / (y2 - y1);
	}

	//�p�����[�^��������(������ɏ���Ă���)����0����1�̊ԂȂ������
	if ((tx == ty) && (0 <= tx ) && (tx <= 1)) {
		return true;
	}
	else {
		return false;
	}
}