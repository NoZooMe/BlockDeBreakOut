#include "Segment.h"



Segment::Segment(float beginX, float beginY, float endX, float endY) : begin(beginX, beginY), end(endX, endY), segment(endX - beginX, endY - beginY){
}

void Segment::UpdateSegment(float beginX, float beginY, float endX, float endY) {
	begin.Setter(beginX, beginY);
	end.Setter(endX, endY);
	segment.Setter(endX - beginX, endY - beginY);
}


bool Segment::CheckOnPoint(const Vector2<float>& point) const{
	
	//座標を代入.慣れてきたら無くてもいい
	//点の座標を代入
	int x = point.GetterX();
	int y = point.GetterY();

	//線分の座標を代入
	int x1 = begin.GetterX();
	int y1 = begin.GetterY();
	int x2 = end.GetterX();
	int y2 = end.GetterY();

	//パラメータを宣言
	int tx, ty;

	//線分の傾きが0または無い場合は個別で計算
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

	//パラメータが等しい(直線状に乗っている)かつ0から1の間なら線分上
	if ((tx == ty) && (0 <= tx ) && (tx <= 1)) {
		return true;
	}
	else {
		return false;
	}
}