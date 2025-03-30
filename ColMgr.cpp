#include "ColMgr.h"
#include <cmath>
#include "DxLib.h"

bool ColMgr::ColVert_RectAndBall(const RectangleObject& rect,const CircleObject& ball) const  {

	if (Col_SegmentAndBall(rect.vertSide1, ball) || Col_SegmentAndBall(rect.vertSide2, ball)) {
		return true;
	}

	return false;
}

bool ColMgr::ColHori_RectAndBall(const RectangleObject& rect, const CircleObject& ball) const {
	if (Col_SegmentAndBall(rect.horiSide1, ball) || Col_SegmentAndBall(rect.horiSide2, ball)) {
		return true;
	}

	return false;
}

bool ColMgr::Col_SegmentAndBall(const Segment& segment, const CircleObject& ball) const {
	//線分の始点から終点へのベクトルと、線分の始点から円の中心へのベクトルを作る
	Vector2<float> vectorA = segment.GetterSegVector();
	Vector2<float> vectorB = ball.GetterPosition() - segment.GetterBegVector();

	//中心と直線との最短距離
	int dist = vectorB.CrossProd(vectorA.Norm());

	//最短距離が半径より小さければ次の判定へ
	if (fabsf(dist) < ball.GetterR()) {
		//線分の終点から円の中心へのベクトルを作る
		Vector2<float> vectorC = ball.GetterPosition() - segment.GetterEndVector();

		//(A, B), (C, B)の内積を求め、正負が違っていれば接触
		int dotProd1 = vectorB.DotProd(vectorA);
		int dotProd2 = vectorC.DotProd(vectorA);

		if ((dotProd1 * dotProd2) <= 0) {
			return true;
		}

		//線分の末端付近が当たっているか調べる
		if (vectorB.Abs() < ball.GetterR() || vectorC.Abs() < ball.GetterR()) {
			return true;
		}

	}

	

	return false;
	
}

int ColMgr::Check_DistPointAndLine(const Vector2<float>& point, const Vector2<float>& lineBegin, const Vector2<float>& lineEnd) const {
	return 0;
}