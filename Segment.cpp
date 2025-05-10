#include "Segment.h"

Segment::Segment() : _begin(), _end(){

}

Segment::Segment(float beginX, float beginY, float endX, float endY) : _begin(beginX, beginY), _end(endX, endY), segment(endX - beginX, endY - beginY){
}

Segment::Segment(Vector2<float> beginVector, Vector2<float> endVector) : _begin(beginVector.GetterX(), beginVector.GetterY()), _end(endVector.GetterX(), endVector.GetterY()), 
segment(endVector.GetterX() - beginVector.GetterX(), endVector.GetterY() - beginVector.GetterY()){

}

void Segment::UpdateSegment(float beginX, float beginY, float endX, float endY) {
	_begin.Setter(beginX, beginY);
	_end.Setter(endX, endY);
	segment.Setter(endX - beginX, endY - beginY);
}

void Segment::UpdateSegment(Vector2<float> begin, Vector2<float> end) {
	_begin.Setter(begin.GetterX(), begin.GetterY());
	_end.Setter(end.GetterX(), end.GetterY());
	segment.Setter(end.GetterX() - begin.GetterX(), end.GetterY() - begin.GetterY());
}

bool Segment::CheckOnPoint(const Vector2<float>& point) const{
	
	//���W����.����Ă����疳���Ă�����
	//�_�̍��W����
	int x = point.GetterX();
	int y = point.GetterY();

	//�����̍��W����
	int x1 = _begin.GetterX();
	int y1 = _begin.GetterY();
	int x2 = _end.GetterX();
	int y2 = _end.GetterY();

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